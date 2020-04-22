#include "AddTransactionPopup.h"

#include <gtkmm/button.h>
#include <gtkmm/entry.h>

AddTransactionPopup::AddTransactionPopup(acc::TransactionInterface &tran)
    : m_transactionInterface(tran), m_logger("AddTransactionPopup") {}

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

  // Get the window and show it
  m_builder->get_widget("addTransactionPopup", m_window);
  m_window->signal_hide().connect([this]() { onHide(); });
  m_window->show();
}

void AddTransactionPopup::onSubmit() {
  LOG(acc::DEBUG, m_logger) << "onSubmit()";

  acc::Transaction data;

  Gtk::Entry *entry = nullptr;
  m_builder->get_widget("nameEntry", entry);
  if (entry) {
    data.name = entry->get_text();
    entry = nullptr;
  }

  m_builder->get_widget("amountEntry", entry);
  if (entry) {
    data.amount = std::stod(entry->get_text());
    entry = nullptr;
  }

  Gtk::Label *label = nullptr;
  m_builder->get_widget("dateLabel", label);
  if (label) {
    std::string tempDate = label->get_text();
    size_t pos = tempDate.find_first_of('/');
    while (pos != std::string::npos) {
      tempDate.replace(pos,1,"");
      pos = tempDate.find_first_of('/',pos);
    }
    data.date = tempDate;
    label = nullptr;
  }

  LOG(acc::DEBUG,m_logger) << "transaction: name: " << data.name << " date: " << data.date << " amount: " << data.amount;


  m_transactionInterface.addTransaction(data);
  m_transactionInterface.requestTransactions();

  destroy();
}
void AddTransactionPopup::onCancel() {
  LOG(acc::DEBUG, m_logger) << "onCancel()";
  destroy();
}

void AddTransactionPopup::onHide() {
  LOG(acc::DEBUG, m_logger) << "onHide()";
  destroy();
}

void AddTransactionPopup::destroy() {
  m_builder.reset();
  delete m_window;
}
