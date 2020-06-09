#ifndef _GTK_ACCOUNTING_APP_ADD_TRANSACTION_POPUP_H_
#define _GTK_ACCOUNTING_APP_ADD_TRANSACTION_POPUP_H_

#include <gtk-accounting/log/LogChannel.h>
#include <gtk-accounting/transaction/TransactionInterface.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

#include "ListStore.h"

class AddTransactionPopup {
 private:
  using DataError = acc::TransactionInterface::DataError;

 public:
  AddTransactionPopup(acc::TransactionInterface &tran);

  void show();

 private:
  void onSubmit();
  void onCancel();
  void onHide();
  void onInsertSuccess();
  void onInvalidData(DataError);

  void destroy();

  void showDateError();

 private:
  acc::TransactionInterface &m_transactionInterface;
  Glib::RefPtr<Gtk::Builder> m_builder;
  Gtk::Window *m_window;
  acc::LogChannel m_logger;

  acc::ScopedConnection m_insertSuccessConn;
  acc::ScopedConnection m_invalidDataConn;
};

#endif  // _GTK_ACCOUNTING_APP_ADD_TRANSACTION_POPUP_H_
