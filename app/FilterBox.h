#ifndef _GTK_ACCOUNTING_APP_FILTER_BOX_H_
#define _GTK_ACCOUNTING_APP_FILTER_BOX_H_

#include <gtk-accounting/filter/FilterInterface.h>
#include <gtk-accounting/log/LogChannel.h>

#include "Builder.h"
#include "ListStore.h"

class FilterBox
{
  public:
    FilterBox(acc::FilterInterface &filterInterface, Builder &builder);

    FilterBox(const FilterBox &);
    FilterBox(FilterBox &&);
    FilterBox &operator=(const FilterBox &);
    FilterBox &operator=(FilterBox &&);

  private:
    void onFiltersReceived(const std::vector<acc::FilterSmall> &filters);
    void onChanged();
    void onNewFilter(uint16_t id);

  private:
    void appendFilter(const acc::FilterSmall &filter, GtkTreeIter &iter);

  private:
    Builder &m_builder;
    ListStore m_listStore;
    sigc::connection m_changeConn;
    acc::ScopedConnection m_filterConn;
    acc::ScopedConnection m_newFilterConn;
    acc::LogChannel m_log;
    acc::FilterInterface &m_filterInterface;
};

#endif // _GTK_ACCOUNTING_APP_FILTER_BOX_H_
