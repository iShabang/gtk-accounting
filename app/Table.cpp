#include "Table.h"

#include <gtk-accounting/Precision.h>
#include <gtk-accounting/Time.h>

#include <iostream>
#include <string>

Table::Table(acc::TransactionInterface &tran, Builder &builder)
    : m_tran(tran),
      m_builder(builder),
      m_tranConn(tran.transactionsReceived().connect(
          [this](std::vector<acc::Transaction> data) { onTransactions(data); })),
      m_align(0.1),
      m_logger("Table") {
  builder.getWidget("tableTreeView", m_treeView);
  m_listStore = Glib::RefPtr<Gtk::ListStore>::cast_static(builder.getObject("dataListStore"));
  setupColumns();
  connectRenderSignals();
  m_tran.requestTransactions();
}

void Table::onTransactions(std::vector<acc::Transaction> data) {
  LOG(acc::DEBUG, m_logger) << "onTransactions(): length: " << data.size();

  if (m_listStore && m_treeView) {
    m_listStore->clear();
    for (auto &&i : data) {
      GtkTreeIter iter;
      gtk_list_store_append(m_listStore->gobj(), &iter);

      gtk_list_store_set(m_listStore->gobj(), &iter, MODEL_SELECT, false, MODEL_NAME,
                         i.name.c_str(), MODEL_DATE, acc::formatDate(i.date).c_str(), MODEL_AMOUNT,
                         acc::floatToString(i.amount).c_str(), MODEL_ID, i.id, -1);
    }
  }
}

void Table::onSelected(GtkCellRendererToggle *renderer, gchar *path, Table *table) {
  LOG(acc::DEBUG, table->m_logger) << "onSelected()";

  if (!renderer) {
    LOG(acc::DEBUG, table->m_logger) << "onSelected(): renderer object is null";
    return;
  }

  if (!path) {
    LOG(acc::DEBUG, table->m_logger) << "onSelected(): data path is null";
    return;
  }

  GtkTreeIter iter;
  GtkTreePath *treePath = gtk_tree_path_new_from_string(path);
  gtk_tree_model_get_iter(GTK_TREE_MODEL(table->m_listStore->gobj()), &iter, treePath);

  GValue selectValue = G_VALUE_INIT;
  GValue idValue = G_VALUE_INIT;
  gtk_tree_model_get_value(GTK_TREE_MODEL(table->m_listStore->gobj()), &iter, MODEL_SELECT,
                           &selectValue);
  gtk_tree_model_get_value(GTK_TREE_MODEL(table->m_listStore->gobj()), &iter, MODEL_ID, &idValue);

  bool select = !g_value_get_boolean(&selectValue);
  uint64_t id = g_value_get_uint64(&idValue);

  LOG(acc::DEBUG, table->m_logger) << "onSelected(): select: " << select << ". id: " << id;

  gtk_list_store_set(table->m_listStore->gobj(), &iter, MODEL_SELECT, select, -1);

  gtk_tree_path_free(treePath);
  g_value_unset(&selectValue);
  g_value_unset(&idValue);

  table->m_tran.selectTransaction(id, select);
}

void Table::setupColumns() {
  addColumnRenderer("name", "text", VIEW_NAME);
  addColumnRenderer("date", "text", VIEW_DATE);
  addColumnRenderer("amount", "text", VIEW_AMOUNT);
}

void Table::connectRenderSignals() {
  GtkCellRendererToggle *cr =
      GTK_CELL_RENDERER_TOGGLE(gtk_builder_get_object(m_builder.getRef(), "selectRender"));

  g_signal_connect(cr, "toggled", G_CALLBACK(Table::onSelected), this);
}

void Table::addColumnRenderer(const std::string &nameBase, const std::string &attribute,
                              int column) {
  std::string columnName = nameBase + "Column";
  std::string renderName = nameBase + "Render";
  GtkTreeViewColumn *vc =
      GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(m_builder.getRef(), columnName.c_str()));
  GtkCellRenderer *cr =
      GTK_CELL_RENDERER(gtk_builder_get_object(m_builder.getRef(), renderName.c_str()));
  if (vc && cr) {
    gtk_tree_view_column_add_attribute(vc, cr, attribute.c_str(), column);
  }
}
