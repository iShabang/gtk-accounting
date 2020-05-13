#ifndef _GTK_ACCOUNTING_APP_MENU_BOX_H_
#define _GTK_ACCOUNTING_APP_MENU_BOX_H_

#include <gtk-accounting/TransactionInterface.h>
#include <gtk-accounting/LogChannel.h>

#include "AddTransactionPopup.h"
#include "FilterWindow.h"
#include "Builder.h"

class MenuBox {
 public:
  MenuBox(acc::TransactionInterface &trans, Builder &builder, AddTransactionPopup &addTranPopup, FilterWindow &filterWindow);

 private:
  void onAdd();
  void onDelete();
  void onImport();
  void onExport();
  void onNewFilter();

 private:
  void connectSignals(Builder &builder);
  void connectClick(Builder &builder, const std::string &widgetName, std::function<void()> method);

 private:
  acc::TransactionInterface &m_tranInterface;
  AddTransactionPopup &m_addTranPopup;
  FilterWindow &m_filterWindow;
  acc::LogChannel m_log;
};

#endif  // _GTK_ACCOUNTING_APP_MENU_BOX_H_
