#include <gtk-accounting/misc/Time.h>
#include <time.h>

#include <sstream>
#include <iomanip>

namespace acc {

std::string formatDate(const std::string date) {
  std::stringstream ss;
  ss << date.substr(0, 2) << "/";
  ss << date.substr(2, 2) << "/";
  ss << date.substr(4, 4);
  return ss.str();
}

Date getCurrentDate() {
  time_t now;
  time(&now);
  struct tm* timeStruct = localtime(&now);
  return {1 + timeStruct->tm_mon, timeStruct->tm_mday, timeStruct->tm_year + 1900};
}

int getMonthDayCount(uint8_t month, uint32_t year) {
  int days = 0;

  if (month < 8) {
    if (month % 2 == 0) {
      if (month == 2) {
        days = isLeapYear(year) ? 29:28;
      } else {
        days = 30;
      }

    } else {
      days = 31;
    }

  } else {
    days = (month % 2 == 0) ? 31 : 30;
  }

  return days;
}

bool isLeapYear(uint32_t year) {
  return year % 4 == 0;
}

std::string dateToString(const Date &date) {
  std::stringstream ss;
  ss << std::setfill('0');
  ss << std::setw(2) << date.month;
  ss << std::setw(2) << date.day;
  ss << date.year;
  return ss.str();
}

DateResult stringToDate(const std::string &dateStr) {

  DateResult result;
  if (dateStr.length() != 8) {
    result.setError("invalid length. expected 8 characters");
    return result;
  }

  Date date;
  date.month = std::stoi(dateStr.substr(0,2));
  date.day = std::stoi(dateStr.substr(2,2));
  date.year = std::stoi(dateStr.substr(4,4));
  result.setSuccess(std::move(date));
  return result;
}

}  // namespace acc
