#ifndef _GTK_ACCOUNTING_APP_TABLE_H_
#define _GTK_ACCOUNTING_APP_TABLE_H_

#include <gtk-accounting/TransactionInterface.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>

#include "Builder.h"

class Table {
 public:
  Table(acc::TransactionInterface &tran, Builder &builder);

 private:
  void onEntrySelect();
  void onTransactions(std::vector<acc::Transaction> data);
  void onDelete();
  Gtk::Box *createTableEntry(const acc::Transaction &transaction);
  void setHeaderAlignment(const float &value);

  void onSelected(Gtk::CheckButton *checkBtn, const uint64_t &id);

 private:
  acc::TransactionInterface &m_tran;
  Builder &m_builder;
  Gtk::Box *m_tableBox;
  acc::ScopedConnection m_tranConn;
  float m_align;
};

#endif  // _GTK_ACCOUNTING_APP_TABLE_H_
