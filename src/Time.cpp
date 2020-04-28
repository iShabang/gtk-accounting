#include <gtk-accounting/Time.h>

#include <sstream>
#include <time.h>

namespace acc {

std::string formatDate(const std::string date)
{
  std::stringstream ss;
  ss << date.substr(0,2) << "/";
  ss << date.substr(2,2) << "/";
  ss << date.substr(4,4);
  return ss.str();
}

Date getCurrentDate() {
  time_t now;
  time(&now);
  struct tm * timeStruct = localtime(&now);
  return { 1+timeStruct->tm_mon, timeStruct->tm_mday, timeStruct->tm_year + 1900};
}

}
