#ifndef _GTK_ACCOUNTING_BUILDER_H_
#define _GTK_ACCOUNTING_BUILDER_H_

#include <gtk/gtk.h>
#include <string>

class Builder {

    public:
    Builder(const std::string &uiDefinition);

    Builder(const Builder &) = delete;
    Builder(Builder &&) = delete;
    Builder& operator=(const Builder &) = delete;
    Builder& operator=(Builder &&) = delete;

    GtkWidget* getWidget(const std::string &name);
    void connectSignals();


    private:
    GtkBuilder* m_builder;

};

#endif // _GTK_ACCOUNTING_BUILDER_H_
