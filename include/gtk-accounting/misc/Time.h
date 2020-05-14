#ifndef _GTK_ACCOUNTING_TIME_H_
#define _GTK_ACCOUNTING_TIME_H_

#include <gtk-accounting/misc/Result.h>

#include <string>

namespace acc {
  struct Date {
    int month;
    int day;
    int year;
  };

  using DateResult = Result<Date,std::string>;

  std::string formatDate(const std::string date);
  Date getCurrentDate();
  int getMonthDayCount(uint8_t month, uint32_t year);
  bool isLeapYear(uint32_t year);
  std::string dateToString(const Date &date);
  DateResult stringToDate(const std::string &dateStr);
}

#endif // _GTK_ACCOUNTING_TIME_H_
