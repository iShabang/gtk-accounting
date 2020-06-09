#include "ComboBoxMethods.h"

#include <gtkmm/combobox.h>

#include "ListStore.h"

void addComboData(Gtk::Builder &builder, const std::string &storeName, const int &start,
                  const int &end)
{
  ListStore store = ListStore::cast_static(builder.get_object(storeName));
  GtkTreeIter iter;
  for (auto i = start; i <= end; i++)
  {
    gtk_list_store_append(GTK_LIST_STORE(store->gobj()), &iter);
    gtk_list_store_set(GTK_LIST_STORE(store->gobj()), &iter, 0, i, -1);
  }
}

GtkWidget *getComboEntry(Gtk::Builder &builder, const std::string &name)
{
  Gtk::ComboBox *comboBox = nullptr;
  builder.get_widget(name.c_str(), comboBox);
  GtkWidget *entry = gtk_bin_get_child(GTK_BIN(comboBox->gobj()));
  return entry;
}

void setComboValue(Gtk::Builder &builder, const std::string &name, const int &value)
{
  GtkWidget *entry = getComboEntry(builder, name);
  gtk_entry_set_text(GTK_ENTRY(entry), std::to_string(value).c_str());
}

std::string getComboText(Gtk::Builder &builder, const std::string &name)
{
  GtkWidget *comboEntry = getComboEntry(builder, name);
  std::string text = gtk_entry_get_text(GTK_ENTRY(comboEntry));
  return text;
}
