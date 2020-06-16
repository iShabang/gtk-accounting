#include "EntryMethods.h"

std::string getEntryText(Gtk::Builder &builder, const std::string &name)
{
  Gtk::Entry *entry = nullptr;
  builder.get_widget(name,entry);

  if (entry)
    return entry->get_text();
  else
    return "";
}

