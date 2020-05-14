#include "AddTransactionPopup.h"

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
  addComboData("monthStore", 1, 12);
  addComboData("dayStore", 1, 31);
  addComboData("yearStore", 2000, 2020);

  // Add current date to combo box entries
  acc::Date currentDate = acc::getCurrentDate();
  setComboValue("monthCombo", currentDate.month);
  setComboValue("dayCombo", currentDate.day);
  setComboValue("yearCombo", currentDate.year);

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
    ss << std::setw(2) << getComboText("monthCombo");
    ss << std::setw(2) << getComboText("dayCombo");
    ss << getComboText("yearCombo");
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

void AddTransactionPopup::addComboData(const std::string &storeName, const int &start,
                                       const int &end) {
  ListStore store = ListStore::cast_static(m_builder->get_object(storeName));
  GtkTreeIter iter;
  for (auto i = start; i <= end; i++) {
    gtk_list_store_append(GTK_LIST_STORE(store->gobj()), &iter);
    gtk_list_store_set(GTK_LIST_STORE(store->gobj()), &iter, 0, std::to_string(i).c_str(), -1);
  }
}

void AddTransactionPopup::setComboValue(const std::string &name, const int &value) {
  GtkWidget *entry = getComboEntry(name);
  gtk_entry_set_text(GTK_ENTRY(entry), std::to_string(value).c_str());
}

std::string AddTransactionPopup::getComboText(const std::string &name) {
  GtkWidget *comboEntry = getComboEntry(name);
  std::string text = gtk_entry_get_text(GTK_ENTRY(comboEntry));
  return text;
}

GtkWidget *AddTransactionPopup::getComboEntry(const std::string &name) {
  Gtk::ComboBox *comboBox = nullptr;
  m_builder->get_widget(name.c_str(), comboBox);
  GtkWidget *entry = gtk_bin_get_child(GTK_BIN(comboBox->gobj()));
  return entry;
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
