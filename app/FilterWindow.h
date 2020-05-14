#ifndef _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_
#define _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_

#include <gtk-accounting/log/LogChannel.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

class FilterWindow
{
    public:
    FilterWindow();

    FilterWindow(const FilterWindow &) = delete;
    FilterWindow(FilterWindow &&) = delete;
    FilterWindow &operator=(const FilterWindow &) = delete;
    FilterWindow &operator=(FilterWindow &&) = delete;

    // Public methods
    void show();

    private:

    // Signal Handlers
    void onHideWindow();

    // Private helper methods
    void destroy();

    private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Window *m_window;

    acc::LogChannel m_log;
};

#endif // _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_
