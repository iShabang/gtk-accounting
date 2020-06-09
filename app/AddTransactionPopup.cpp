#include "AddTransactionPopup.h"
#include "ComboBoxMethods.h"

#include <gtk-accounting/misc/Time.h>
#include <gtkmm/button.h>
#include <gtkmm/combobox.h>

#include <iomanip>
#include <sstream>
#include <string>

AddTransactionPopup::AddTransactionPopup(acc::TransactionInterface &tran)
    : m_transactionInterface(tran),
      m_logger("AddTransactionPopup"),
      m_insertSuccessConn(tran.insertSuccess().connect([this]() { onInsertSuccess(); })),
      m_invalidDataConn(
          tran.invalidData().connect([this](DataError error) { onInvalidData(error); })) {}

void AddTransactionPopup::show() {
  // Create Builder instance of popup window
  m_builder = Gtk::Builder::create_from_file("../glade/add-transaction-window.glade");

  // Get the buttons and connect the signals
  Gtk::Button *submitButton = nullptr;
  m_builder->get_widget("submitButton", submitButton);
  submitButton->signal_clicked().connect([this]() { onSubmit(); });

  Gtk::Button *cancelButton = nullptr;
  m_builder->get_widget("cancelButton", cancelButton);
  cancelButton->signal_clicked().connect([this]() { onCancel(); });

  // Setup combo box stores
  acc::Date currentDate = acc::getCurrentDate();
  addComboData(*m_builder.get(), "monthStore", 1, 12);
  addComboData(*m_builder.get(), "dayStore", 1, 31);
  addComboData(*m_builder.get(), "yearStore", currentDate.year - 20, currentDate.year);

  // Add current date to combo box entries
  setComboValue(*m_builder.get(), "monthCombo", currentDate.month);
  setComboValue(*m_builder.get(), "dayCombo", currentDate.day);
  setComboValue(*m_builder.get(), "yearCombo", currentDate.year);

  // Get the window and show it
  m_builder->get_widget("addTransactionPopup", m_window);
  m_window->signal_hide().connect([this]() { onHide(); });
  m_window->show();
}

void AddTransactionPopup::onSubmit() {
  bool success = true;
  acc::Transaction data;

  Gtk::Entry *entry = nullptr;
  m_builder->get_widget("nameEntry", entry);
  success += entry != nullptr;
  if (success) {
    data.name = entry->get_text();
    entry = nullptr;
  }

  m_builder->get_widget("amountEntry", entry);
  success += entry != nullptr;
  if (success) {
    data.amount = std::stod(entry->get_text());
    entry = nullptr;
  }

  if (success) {
    std::stringstream ss;
    ss << std::setfill('0');
    ss << getComboText(*m_builder.get(), "yearCombo") << "-";
    ss << std::setw(2) << getComboText(*m_builder.get(), "monthCombo") << "-";
    ss << std::setw(2) << getComboText(*m_builder.get(), "dayCombo");
    data.date = ss.str();
  }

  if (success) {
    LOG(acc::DEBUG, m_logger) << "onSubmit(): transaction: name: " << data.name
                              << " date: " << data.date << " amount: " << data.amount;

    m_transactionInterface.addTransaction(data);
    m_transactionInterface.requestTransactions();
  } else {
    LOG(acc::DEBUG, m_logger) << "onSubmit(): Failed to retrieve data from GTK";
  }
}

void AddTransactionPopup::onCancel() {
  LOG(acc::DEBUG, m_logger) << "onCancel()";
  destroy();
}

void AddTransactionPopup::onHide() {
  LOG(acc::DEBUG, m_logger) << "onHide()";
  destroy();
}

void AddTransactionPopup::onInsertSuccess() { destroy(); }

void AddTransactionPopup::onInvalidData(DataError error) {
  LOG(acc::DEBUG, m_logger) << "onInvalidData(): error " << error;
  if (error == acc::TransactionInterface::DATE) {
    showDateError();
  }
}

void AddTransactionPopup::destroy() {
  m_builder.reset();
  delete m_window;
}

void AddTransactionPopup::showDateError() {
  // update the label to show a date error message
  Gtk::Label *label = nullptr;
  m_builder->get_widget("addTransactionLabel",label);
  if (!label) {
    LOG(acc::DEBUG,m_logger) << "showDateError: label not found";
    return;
  }

  label->set_text("Invalid date entered");
  // maybe turn the label red
}
