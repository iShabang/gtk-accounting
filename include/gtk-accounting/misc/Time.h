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

  /* Gets the current date and stores the day, month, and year in a custom Date object */
  Date getCurrentDate();

  /* Retrieves the number of days in the selected month. The year is required in order to
   * account for leap years. This only affects the month of February (02) */
  int getMonthDayCount(uint8_t month, uint32_t year);

  /* Test if the current year is a leap year */
  bool isLeapYear(uint32_t year);

  /* Formats a Date object into a string that can be stored easier */
  std::string dateToString(const Date &date);

  /* Converts the passed string into a Date object. If the YYYY-MM-DD format is not used, then an
   * error is returned in the Result object */
  DateResult stringToDate(const std::string &dateStr);
}

#endif // _GTK_ACCOUNTING_TIME_H_
