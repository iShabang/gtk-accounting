#ifndef _GTK_ACCOUNTING_APP_ADD_TRANSACTION_POPUP_H_
#define _GTK_ACCOUNTING_APP_ADD_TRANSACTION_POPUP_H_

#include <gtk-accounting/LogChannel.h>
#include <gtk-accounting/TransactionInterface.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

class AddTransactionPopup {
 public:
  AddTransactionPopup(acc::TransactionInterface &tran);

  void show();

 private:
  void onSubmit();
  void onCancel();
  void onHide();

  void destroy();

 private:
  acc::TransactionInterface &m_transactionInterface;
  Glib::RefPtr<Gtk::Builder> m_builder;
  Gtk::Window *m_window;
  acc::LogChannel m_logger;
};

#endif  // _GTK_ACCOUNTING_APP_ADD_TRANSACTION_POPUP_H_
