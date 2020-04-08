#include "Facade.h"

Facade::Facade(){
  m_builder = Gtk::Builder::create_from_file("../glade/main-window.glade");
  gtk_builder_connect_signals(m_builder->gobj(),nullptr);
}

Glib::RefPtr<Gtk::Builder> Facade::builder() { return m_builder; }
