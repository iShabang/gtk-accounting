#include "Builder.h"

Builder::Builder(const std::string &uiDefinition){
    m_builder = gtk_builder_new_from_file(uiDefinition.c_str());
}

GtkWidget* Builder::getWidget(const std::string &name){
    return GTK_WIDGET(gtk_builder_get_object(m_builder,name.c_str()));
}

void Builder::connectSignals(){
    gtk_builder_connect_signals(m_builder,nullptr);
}
