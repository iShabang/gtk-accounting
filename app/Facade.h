#ifndef _GTK_ACCOUNTING_APP_FACADE_H_
#define _GTK_ACCOUNTING_APP_FACADE_H_

#include "Builder.h"

#include <gtkmm/builder.h>

class Facade
{
    public:
    Facade();

    Glib::RefPtr<Gtk::Builder> builder();


    private:
    Glib::RefPtr<Gtk::Builder> m_builder;
};

#endif // _GTK_ACCOUNTING_APP_FACADE_H_
