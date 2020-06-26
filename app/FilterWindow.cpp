#include "FilterWindow.h"

#include <gtk-accounting/filter/Filter.h>
#include <gtk-accounting/misc/Time.h>
#include <gtkmm/button.h>
#include <sstream>
#include <iomanip>

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

  Gtk::Button *button = nullptr;
  m_builder->get_widget("submitButton", button);
  if (button)
  {
    button->signal_clicked().connect([this]() { onSubmit(); });
  }

  //TODO: Move button signal connection to separate function.
  m_builder->get_widget("cancelButton", button);
  if (button)
  {
    button->signal_clicked().connect([this](){onHideWindow();});
  }

  m_builder->get_widget("mainWindow", m_window);
  m_window->signal_hide().connect([this]() { onHideWindow(); });
  m_window->show();
}

void FilterWindow::onHideWindow() { destroy(); }

void FilterWindow::onSubmit()
{

  std::stringstream ss;

  acc::Filter filter;
  getDate("start",filter.dateMin);
  getDate("end",filter.dateMax);

  filter.amountMin = getEntryText(*m_builder.get(), "amountStart");
  filter.amountMax = getEntryText(*m_builder.get(), "amountEnd");

  filter.pattern = getEntryText(*m_builder.get(), "pattern");
  filter.name = getEntryText(*m_builder.get(), "nameEntry");

  m_filterInterface.addFilter(filter);
  destroy();
}


void FilterWindow::destroy()
{
  m_builder.reset();
  delete m_window;
}

void FilterWindow::getDate(const std::string &prefix, std::string &dest)
{
  std::string year = getComboText(*m_builder.get(), prefix+"ComboYear");
  std::string month = getComboText(*m_builder.get(), prefix+"ComboMonth");
  std::string day = getComboText(*m_builder.get(), prefix+"ComboDay");

  if (!year.length() || !month.length() || !day.length())
  {
    return;
  }

  std::stringstream ss;
  ss << year;
  ss << std::setfill('0') << std::right;
  ss << std::setw(2) << month;
  ss << std::setw(2) << day;

  if (ss.str().length() == 8)
  {
    dest = ss.str();
    acc::addHyphens(dest);
  }
}
