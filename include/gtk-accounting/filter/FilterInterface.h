#ifndef _GTK_ACCOUNTING_FILTER_INTERFACE_H_
#define _GTK_ACCOUNTING_FILTER_INTERFACE_H_

#include <gtk-accounting/filter/Filter.h>

namespace acc
{
  class FilterInterface
  {
    public:
      virtual ~FilterInterface() {}

      virtual void addFilter(const Filter &filter) = 0;
      virtual void deleteFilter(uint16_t id) = 0;
      virtual void selectFilter(uint16_t id) = 0;
  };
}

#endif // _GTK_ACCOUNTING_FILTER_INTERFACE_H_
