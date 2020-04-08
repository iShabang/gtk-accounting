#include "Facade.h"

#include <iostream>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

int main(int argc, char **argv) {

  auto app = Gtk::Application::create(argc, argv, "gtk-accounting");

  Facade facade;

  Gtk::Window* window = nullptr;

  facade.builder()->get_widget("mainWindow", window);

  if (window){
    std::cout << "got window" << std::endl;
    window->set_default_size(200, 200);
    app->run(*window);
  } else {
    std::cout << "window not found" << std::endl;
  }

  delete window;

  return 0;
}
