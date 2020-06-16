#include "FilterWindow.h"

#include <gtk-accounting/filter/Filter.h>
#include <gtk-accounting/misc/Time.h>
#include <gtkmm/button.h>
#include <sstream>

#include "ComboBoxMethods.h"
#include "EntryMethods.h"

FilterWindow::FilterWindow(acc::FilterInterface &filter) : m_filterInterface(filter), m_log("FilterWindow") {}

void FilterWindow::show()
{
  m_builder = Gtk::Builder::create_from_file("../glade/filter-window.glade");

  // Setup combo box stores
  acc::Date curDate = acc::getCurrentDate();
  addComboData(*m_builder.get(), "monthStore", 1, 12);
  addComboData(*m_builder.get(), "dayStore", 1, 31);
  addComboData(*m_builder.get(), "yearStore", curDate.year - 20, curDate.year);

  Gtk::Button *submit = nullptr;
  m_builder->get_widget("submitButton", submit);
  if (submit)
  {
    submit->signal_clicked().connect([this]() { onSubmit(); });
  }

  m_builder->get_widget("mainWindow", m_window);
  m_window->signal_hide().connect([this]() { onHideWindow(); });
  m_window->show();
}

void FilterWindow::onHideWindow() { destroy(); }

void FilterWindow::onSubmit()
{

  std::stringstream ss;
  ss << getComboText(*m_builder.get(), "startComboYear") << "-" << getComboText(*m_builder.get(), "startComboMonth") << "-" << getComboText(*m_builder.get(), "startComboDay");

  acc::Filter filter;
  filter.dateMin = ss.str();

  ss.str("");
  ss << getComboText(*m_builder.get(), "endComboYear") << "-" << getComboText(*m_builder.get(), "endComboMonth") << "-" << getComboText(*m_builder.get(), "endComboDay");
  filter.dateMax = ss.str();

  filter.amountMin = getEntryText(*m_builder.get(), "amountStart");
  filter.amountMax = getEntryText(*m_builder.get(), "amountEnd");

  filter.pattern = getEntryText(*m_builder.get(), "pattern");
  filter.name = getEntryText(*m_builder.get(), "nameEntry");

  m_filterInterface.addFilter(filter);
}


void FilterWindow::destroy()
{
  m_builder.reset();
  delete m_window;
}
