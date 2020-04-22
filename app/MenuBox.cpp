#include "MenuBox.h"

#include <gtkmm/button.h>

MenuBox::MenuBox(acc::TransactionInterface &trans, Builder &builder,
                 AddTransactionPopup &addTranPopup)
    : m_tranInterface(trans), m_addTranPopup(addTranPopup) {
  Gtk::Button *addButton = nullptr;
  builder.getWidget("addTransactionButton", addButton);
  if (addButton) {
    addButton->signal_clicked().connect([this]() { onAdd(); });
  }
}

void MenuBox::onAdd() { m_addTranPopup.show(); }
