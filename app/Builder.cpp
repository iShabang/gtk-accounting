#include "Builder.h"
#include <iostream>

Builder::Builder(const std::string &uiDefinition) {
  m_builder = Gtk::Builder::create_from_file(uiDefinition);
}

void Builder::getWidget(const std::string &name, Gtk::Widget *result) {
  if (isValid()){
    m_builder->get_widget(name, result);
  }
}

void Builder::connectSignals() {
  if (isValid()){
    gtk_builder_connect_signals(m_builder->gobj(), nullptr);
  }
}

bool Builder::isValid() {
  if (!m_builder) {
    std::cout << "builder not valid" << std::endl;
    return false;
  } else {
    return true;
  }
}
