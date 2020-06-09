#include "FilterWindow.h"

#include <gtk-accounting/misc/Time.h>

#include "ComboBoxMethods.h"

FilterWindow::FilterWindow() : m_log("FilterWindow") {}

void FilterWindow::show()
{
  m_builder = Gtk::Builder::create_from_file("../glade/filter-window.glade");

  // Setup combo box stores
  acc::Date curDate = acc::getCurrentDate();
  addComboData(*m_builder.get(), "monthStore", 1, 12);
  addComboData(*m_builder.get(), "dayStore", 1, 31);
  addComboData(*m_builder.get(), "yearStore", curDate.year - 20, curDate.year);

  m_builder->get_widget("mainWindow", m_window);
  m_window->signal_hide().connect([this]() { onHideWindow(); });
  m_window->show();
}

void FilterWindow::onHideWindow() { destroy(); }

void FilterWindow::destroy()
{
  m_builder.reset();
  delete m_window;
}
