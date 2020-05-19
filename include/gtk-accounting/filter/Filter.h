#ifndef _GTK_ACCOUNTING_FILTER_H_
#define _GTK_ACCOUNTING_FILTER_H_

#include <string>

namespace acc
{
  struct Filter
  {
    bool hasDate;
    bool hasAmount;
    bool hasPattern;

    std::string dateMin;
    std::string dateMax;

    std::string amountMin;
    std::string amountMax;

    std::string pattern;

    std::string name;
  };
}

#endif // _GTK_ACCOUNTING_FILTER_H_
