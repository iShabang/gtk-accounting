#ifndef _GTK_ACCOUNTING_APP_COMBO_BOX_METHODS_H_
#define _GTK_ACCOUNTING_APP_COMBO_BOX_METHODS_H_

#include <string>
#include <gtkmm/builder.h>

/* Adds a sequence of numbers to the combo box store. Used for adding date selection values to the combo box */
void addComboData(Gtk::Builder &builder, const std::string &storeName, const int &start, const int &end);

/* Returns the entry box attached to a combo box. */
GtkWidget * getComboEntry(Gtk::Builder &builder, const std::string &name);

/* Sets the value of the entry in a combo box */
void setComboValue(Gtk::Builder &builder, const std::string &name, const int &value);

/* Returns the current text in the entry within the combo box */
std::string getComboText(Gtk::Builder &builder, const std::string &name);

#endif  // _GTK_ACCOUNTING_APP_COMBO_BOX_METHODS_H_
