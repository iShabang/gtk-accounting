#ifndef _GTK_ACCOUNTING_BUILDER_H_
#define _GTK_ACCOUNTING_BUILDER_H_

#include <gtkmm/builder.h>
#include <string>

class Builder {

    public:
    Builder(const std::string &uiDefinition);

    Builder(const Builder &) = delete;
    Builder(Builder &&) = delete;
    Builder& operator=(const Builder &) = delete;
    Builder& operator=(Builder &&) = delete;

    void getWidget(const std::string &name, Gtk::Widget* result);
    void connectSignals();
    bool isValid();

    private:
    Glib::RefPtr<Gtk::Builder> m_builder;

};

#endif // _GTK_ACCOUNTING_BUILDER_H_
