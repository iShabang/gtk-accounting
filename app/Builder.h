#ifndef _GTK_ACCOUNTING_APP_BUILDER_H_
#define _GTK_ACCOUNTING_APP_BUILDER_H_

#include <gtkmm/builder.h>

class Builder {
  public:
    Builder();
    
    ~Builder() = default;
    Builder(const Builder &) = delete;
    Builder(Builder &&) = delete;
    Builder& operator=(const Builder &) = delete;
    Builder& operator=(Builder &&) = delete;

    template<class T>
    void getWidget(const std::string &name, T*& widget) {
      m_builder->get_widget(name, widget);
    }

  private:
    Glib::RefPtr<Gtk::Builder> m_builder;
};

#endif // _GTK_ACCOUNTING_APP_BUILDER_H_
