#include "FilterBox.h"

#include <gtkmm/combobox.h>

FilterBox::FilterBox(acc::FilterInterface &filterInterface, Builder &builder)
    : m_builder(builder),
      m_filterConn(filterInterface.filtersReceived().connect(
          [this](const std::vector<acc::FilterSmall> &filters) { onFiltersReceived(filters); })),
      m_newFilterConn(filterInterface.newFilter().connect([this](uint16_t id){ onNewFilter(id);})),
      m_log("FilterBox"),
      m_filterInterface(filterInterface)
{
  m_listStore = ListStore::cast_static(m_builder.getObject("filterStore"));
  filterInterface.requestFilters();
  Gtk::ComboBox *combo = nullptr;
  m_builder.getWidget("filterCombo",combo);

  if (combo)
  {
    combo->signal_changed().connect([this](){ onChanged(); });
  }
}

void FilterBox::onFiltersReceived(const std::vector<acc::FilterSmall> &filters)
{
  m_listStore->clear();
  GtkTreeIter iter;
  for (auto &&i : filters)
  {
    appendFilter(i,iter);
  }
}

void FilterBox::onChanged()
{
  Gtk::ComboBox *comboBox = nullptr;
  m_builder.getWidget("filterCombo", comboBox);
  if (!comboBox)
  {
    return;
  }

  GtkTreeIter iter;
  gtk_combo_box_get_active_iter(comboBox->gobj(),&iter);

  GValue nameValue = G_VALUE_INIT;
  GValue idValue = G_VALUE_INIT;
  gtk_tree_model_get_value(GTK_TREE_MODEL(m_listStore->gobj()), &iter, 0,
                           &nameValue);
  gtk_tree_model_get_value(GTK_TREE_MODEL(m_listStore->gobj()), &iter, 1, &idValue);

  std::string name = g_value_get_string(&nameValue);
  uint32_t id = g_value_get_uint(&idValue);

  LOG(acc::DEBUG,m_log) << "onChanged(): name: " << name << " id: " << id;

  g_value_unset(&nameValue);
  g_value_unset(&idValue);

  m_filterInterface.selectFilter(id);
}

void FilterBox::onNewFilter(uint16_t id)
{
  (void) id;
  m_filterInterface.requestFilters();
}

void FilterBox::appendFilter(const acc::FilterSmall &filter, GtkTreeIter &iter)
{
    gtk_list_store_append(GTK_LIST_STORE(m_listStore->gobj()), &iter);
    gtk_list_store_set(GTK_LIST_STORE(m_listStore->gobj()), &iter, 0, filter.name.c_str(), 1, filter.id, -1);
}
