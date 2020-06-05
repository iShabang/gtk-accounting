#ifndef _GTK_ACCOUNTING_FILTER_H_
#define _GTK_ACCOUNTING_FILTER_H_

#include <string>

namespace acc
{
  struct Filter
  {
    std::string dateMin;
    std::string dateMax;

    std::string amountMin;
    std::string amountMax;

    std::string pattern;

    std::string name;
  };

  struct FilterSmall
  {
    uint16_t id;
    std::string name;
  };

}

#endif // _GTK_ACCOUNTING_FILTER_H_
