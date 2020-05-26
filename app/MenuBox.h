#ifndef _GTK_ACCOUNTING_APP_MENU_BOX_H_
#define _GTK_ACCOUNTING_APP_MENU_BOX_H_

#include <gtk-accounting/log/LogChannel.h>
#include <gtk-accounting/transaction/TransactionInterface.h>

#include "AddTransactionPopup.h"
#include "Builder.h"
#include "FilterBox.h"
#include "FilterWindow.h"

class MenuBox
{
 public:
  MenuBox(acc::FilterInterface &filter, acc::TransactionInterface &trans, Builder &builder,
          AddTransactionPopup &addTranPopup, FilterWindow &filterWindow);

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
  FilterBox m_filterBox;
};

#endif  // _GTK_ACCOUNTING_APP_MENU_BOX_H_
