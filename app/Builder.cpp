#include "Builder.h"

#include <iostream>


Builder::Builder() {
  m_builder = Gtk::Builder::create_from_file("../glade/main-window.glade");
  gtk_builder_connect_signals(m_builder->gobj(),nullptr);
}
