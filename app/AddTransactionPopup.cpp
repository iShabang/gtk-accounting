#include "AddTransactionPopup.h"

#include <gtk-accounting/Time.h>
#include <gtkmm/button.h>
#include <gtkmm/combobox.h>

#include <string>

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

  // Get combo boxes and list stores
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

  LOG(acc::DEBUG, m_logger) << "transaction: name: " << data.name << " date: " << data.date
                            << " amount: " << data.amount;

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

void AddTransactionPopup::addComboData(const std::string &storeName, const int &start,
                                       const int &end) {
  list_store store = list_store::cast_static(m_builder->get_object(storeName));
  GtkTreeIter iter;
  for (auto i = start; i <= end; i++) {
    LOG(acc::DEBUG, m_logger) << "addComboData(): appending month: " << i << " to monthStore";
    gtk_list_store_append(GTK_LIST_STORE(store->gobj()), &iter);
    LOG(acc::DEBUG, m_logger) << "addComboData(): column appended";
    gtk_list_store_set(GTK_LIST_STORE(store->gobj()), &iter, 0, std::to_string(i).c_str(), -1);
    LOG(acc::DEBUG, m_logger) << "addComboData(): data added";
  }
}

void AddTransactionPopup::setComboValue(const std::string &name, const int &value) {
  Gtk::ComboBox *comboBox = nullptr;
  m_builder->get_widget(name.c_str(), comboBox);
  GtkWidget *entry = gtk_bin_get_child(GTK_BIN(comboBox->gobj()));
  gtk_entry_set_text(GTK_ENTRY(entry), std::to_string(value).c_str());
}
