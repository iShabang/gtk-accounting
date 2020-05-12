#include "FilterWindow.h"

FilterWindow::FilterWindow() : m_log("FilterWindow")
{
}

void FilterWindow::show()
{
    m_builder = Gtk::Builder::create_from_file("../glade/filter-window.glade");

    m_builder->get_widget("mainWindow",m_window);
    m_window->signal_hide().connect([this](){ onHideWindow(); });
}

void FilterWindow::onHideWindow()
{
    destroy();
}

void FilterWindow::destroy()
{
}
