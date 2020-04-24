#ifndef _GTK_ACCOUNTING_APP_MENU_BOX_H_
#define _GTK_ACCOUNTING_APP_MENU_BOX_H_

#include <gtk-accounting/TransactionInterface.h>
#include <gtk-accounting/LogChannel.h>

#include "AddTransactionPopup.h"
#include "Builder.h"

class MenuBox {
 public:
  MenuBox(acc::TransactionInterface &trans, Builder &builder, AddTransactionPopup &addTranPopup);

 private:
  void onAdd();
  void onDelete();
  void onImport();
  void onExport();

 private:
  void connectSignals(Builder &builder);

 private:
  acc::TransactionInterface &m_tranInterface;
  AddTransactionPopup &m_addTranPopup;
  acc::LogChannel m_log;
};

#endif  // _GTK_ACCOUNTING_APP_MENU_BOX_H_
