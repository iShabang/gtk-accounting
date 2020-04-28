#ifndef _GTK_ACCOUNTING_TIME_H_
#define _GTK_ACCOUNTING_TIME_H_

#include <string>

namespace acc {
  struct Date {
    int month;
    int day;
    int year;
  };

  std::string formatDate(const std::string date);
  Date getCurrentDate();
}

#endif // _GTK_ACCOUNTING_TIME_H_
