#include <gtk/gtk.h>
#include <iostream>

int main(int argc, char **argv) {
  GtkWidget *mainwin;
  // Initialize i18n support with bindtextdomain(), etc.

  // ...

  // Initialize the widget set
  gtk_init(&argc, &argv);

  // Create the main window
  mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Set up our GUI elements

  // ...

  // Show the application window
  gtk_widget_show_all(mainwin);

  // Enter the main event loop, and wait for user interaction
  gtk_main();

  // The user lost interest
  return 0;
}
