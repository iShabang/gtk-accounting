#include "MenuBox.h"

#include <gtkmm/button.h>

MenuBox::MenuBox(acc::TransactionInterface &trans, Builder &builder,
                 AddTransactionPopup &addTranPopup,
                 FilterWindow &filterWindow)
    : m_tranInterface(trans), m_addTranPopup(addTranPopup), m_filterWindow(filterWindow), m_log("MenuBox") {
  connectSignals(builder);
}

void MenuBox::onAdd() { m_addTranPopup.show(); }

void MenuBox::onDelete() {
  LOG(acc::DEBUG, m_log) << "onDelete()";
  m_tranInterface.deleteSelected();
  m_tranInterface.requestTransactions();
}

void MenuBox::onNewFilter()
{
  m_filterWindow.show();
}

void MenuBox::connectSignals(Builder &builder) {
  connectClick(builder,"addTransactionButton",[this](){ onAdd(); });
  connectClick(builder,"deleteTransactionButton",[this](){ onDelete(); });
  connectClick(builder,"newFilterButton",[this](){ onNewFilter(); });
}

void MenuBox::connectClick(Builder &builder, const std::string &widgetName, std::function<void()> method)
{
  Gtk::Button *button = nullptr;
  builder.getWidget(widgetName,button);
  if (button)
  {
    button->signal_clicked().connect(method);
  }
}
