#ifndef _GTK_ACCOUNTING_APP_TABLE_H_
#define _GTK_ACCOUNTING_APP_TABLE_H_

#include "Builder.h"

#include <gtk-accounting/TransactionInterface.h>
#include <gtk-accounting/ScopedConnection.h>

#include <gtkmm/box.h>

class Table {

  public:
    Table(acc::TransactionInterface &tran, Builder& builder); 

  private:
    void onEntrySelect();
    void onTransactions(std::vector<acc::Transaction> data);
    void onDelete();

  private:
    acc::TransactionInterface &m_tran;
    Builder &m_builder;

    acc::ScopedConnection m_tranConn;
    Gtk::Box *m_tableBox;
};

#endif // _GTK_ACCOUNTING_APP_TABLE_H_
