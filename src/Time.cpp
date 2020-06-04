#include <gtk-accounting/misc/Time.h>
#include <time.h>

#include <iomanip>
#include <sstream>

namespace acc
{
Date getCurrentDate()
{
  time_t now;
  time(&now);
  struct tm *timeStruct = localtime(&now);
  return {1 + timeStruct->tm_mon, timeStruct->tm_mday, timeStruct->tm_year + 1900};
}

int getMonthDayCount(uint8_t month, uint32_t year)
{
  int days = 0;

  if (month < 8)
  {
    if (month % 2 == 0)
    {
      if (month == 2)
      {
        days = isLeapYear(year) ? 29 : 28;
      }
      else
      {
        days = 30;
      }
    }
    else
    {
      days = 31;
    }
  }
  else
  {
    days = (month % 2 == 0) ? 31 : 30;
  }

  return days;
}

bool isLeapYear(uint32_t year) { return year % 4 == 0; }

std::string dateToString(const Date &date)
{
  std::stringstream ss;
  ss << std::setfill('0') << date.year << "-" << std::setw(2) << date.month << "-" << std::setw(2)
     << date.day;
  return ss.str();
}

DateResult stringToDate(const std::string &dateStr)
{
  DateResult result;
  if (dateStr.length() != 10)
  {
    result.setError("invalid length. expected 10 characters");
    return result;
  }

  Date date;
  try
  {
    date.year = std::stoi(dateStr.substr(0, 4));
    date.month = std::stoi(dateStr.substr(5, 2));
    date.day = std::stoi(dateStr.substr(8, 2));
    result.setSuccess(std::move(date));
  }
  catch (std::invalid_argument &e)
  {
    result.setError("Invalid characters"); 
  }
  return result;
}

}  // namespace acc
