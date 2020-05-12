#ifndef _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_
#define _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_

#include <gtk-accounting/LogChannel.h>
#include <gtkmm/builder.h>

class FilterWindow
{
    public:
    FilterWindow();

    FilterWindow(const FilterWindow &) = 0;
    FilterWindow(FilterWindow &&) = 0;
    FilterWindow &operator=(const FilterWindow &) = 0;
    FilterWindow &operator=(FilterWindow &&) = 0;

    void show();

    private:
    void onHideWindow();

    void destroy();

    private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Window *m_window;

    acc::LogChannel m_log;
};

#endif // _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_
