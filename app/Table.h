#ifndef _GTK_ACCOUNTING_APP_TABLE_H_
#define _GTK_ACCOUNTING_APP_TABLE_H_

#include <gtk-accounting/log/LogChannel.h>
#include <gtk-accounting/transaction/TransactionInterface.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>

#include "Builder.h"

enum ViewColumns
{
  VIEW_SELECT,
  VIEW_NAME,
  VIEW_DATE,
  VIEW_AMOUNT,
  VIEW_NUM_COLUMNS
};

enum ModelColumns
{
  MODEL_SELECT,
  MODEL_NAME,
  MODEL_DATE,
  MODEL_AMOUNT,
  MODEL_ID,
  MODEL_NUM_COLUMNS
};

class Table
{
 public:
  Table(acc::TransactionInterface &tran, Builder &builder);

 private:
  void onTransactions(std::vector<acc::Transaction> data);

  static void onSelected(GtkCellRendererToggle *renderer, gchar *path, Table *table);

  void setupColumns();
  void connectRenderSignals();
  void addColumnRenderer(const std::string &nameBase, const std::string &attribute, int column);

 private:
  acc::TransactionInterface &m_tran;
  Builder &m_builder;
  Gtk::TreeView *m_treeView;
  Glib::RefPtr<Gtk::ListStore> m_listStore;
  acc::ScopedConnection m_tranConn;
  float m_align;
  acc::LogChannel m_logger;
};

#endif  // _GTK_ACCOUNTING_APP_TABLE_H_
