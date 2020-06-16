#ifndef _GTK_ACCOUNTING_APP_ENTRY_METHODS_H_
#define _GTK_ACCOUNTING_APP_ENTRY_METHODS_H_

#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <string>

std::string getEntryText(Gtk::Builder &builder, const std::string &name);

#endif // _GTK_ACCOUNTING_APP_ENTRY_METHODS_H_
