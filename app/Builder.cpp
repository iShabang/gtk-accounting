#include "Builder.h"

#include <iostream>


Builder::Builder() {
  m_builder = Gtk::Builder::create_from_file("../glade/main-window.glade");
  gtk_builder_connect_signals(m_builder->gobj(),nullptr);
}

Glib::RefPtr<Glib::Object> Builder::getObject(const std::string &name) {
  return m_builder->get_object(name);
}

GtkBuilder * Builder::getRef() {
  return m_builder->gobj();
}
