#include "MenuBox.h"

#include <gtkmm/button.h>

MenuBox::MenuBox(acc::TransactionInterface &trans, Builder &builder,
                 AddTransactionPopup &addTranPopup)
    : m_tranInterface(trans), m_addTranPopup(addTranPopup), m_log("MenuBox") {
  connectSignals(builder);
}

void MenuBox::onAdd() { m_addTranPopup.show(); }

void MenuBox::onDelete() {
  LOG(acc::DEBUG, m_log) << "onDelete()";
  m_tranInterface.deleteSelected();
  m_tranInterface.requestTransactions();
}

void MenuBox::connectSignals(Builder &builder) {
  Gtk::Button *addButton = nullptr;
  builder.getWidget("addTransactionButton", addButton);
  if (addButton) {
    addButton->signal_clicked().connect([this]() { onAdd(); });
  }

  Gtk::Button *deleteButton = nullptr;
  builder.getWidget("deleteTransactionButton", deleteButton);
  if (deleteButton) {
    deleteButton->signal_clicked().connect([this]() { onDelete(); });
  }
}
