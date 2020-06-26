#ifndef _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_
#define _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_

#include <gtk-accounting/log/LogChannel.h>
#include <gtk-accounting/filter/FilterInterface.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

class FilterWindow
{
    public:
    FilterWindow(acc::FilterInterface &filter);

    FilterWindow(const FilterWindow &) = delete;
    FilterWindow(FilterWindow &&) = delete;
    FilterWindow &operator=(const FilterWindow &) = delete;
    FilterWindow &operator=(FilterWindow &&) = delete;

    // Public methods
    void show();

    private:

    // Signal Handlers
    void onHideWindow();
    void onSubmit();

    // Private helper methods
    void destroy();
    void getDate(const std::string &prefix, std::string &dest);

    private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Window *m_window;

    acc::FilterInterface &m_filterInterface;
    acc::LogChannel m_log;
};

#endif // _GTK_ACCOUNTING_APP_FILTER_WINDOW_H_
