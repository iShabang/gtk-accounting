#include "Facade.h"

#include <gtk-accounting/LibFacade.h>
#include <iostream>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

int main(int argc, char **argv) {

  // Initialize library
  acc::LibFacade libFacadeImpl;
  acc::LibFacadeInterface &libInterface = libFacadeImpl;

  if (!libInterface.database().isOpen()) {
    std::cerr << "Main(): failed to open database. Aborting\n";
    return 1;
  }

  // Initialize gtk
  auto app = Gtk::Application::create(argc, argv, "gtk-accounting");

  Facade facade(libInterface);

  Gtk::Window* window = nullptr;

  facade.builder().getWidget("mainWindow",window);

  if (window){
    window->set_default_size(200, 200);
    app->run(*window);
  } else {
    std::cerr << "Main(): builder window not found\n";
  }

  delete window;

  return 0;
}
