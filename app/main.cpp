#include "Facade.h"

#include <gtk/gtk.h>
#include <iostream>

int main(int argc, char **argv) {

  GtkWidget *mainwin;

  // Initialize the widget set
  gtk_init(&argc, &argv);

  // Initialize application
  Facade app;

  // Connect gtk signals
  app.builder().connectSignals();

  // Show the application window
  mainwin = app.builder().getWidget("mainWindow");
  gtk_widget_show_all(mainwin);

  // Enter the main event loop, and wait for user interaction
  gtk_main();

  // The user lost interest
  return 0;
}
