#include <gtk-accounting/Time.h>

#include <sstream>

namespace acc {

std::string formatDate(const std::string date)
{
  std::stringstream ss;
  ss << date.substr(0,2) << "/";
  ss << date.substr(2,2) << "/";
  ss << date.substr(4,4);
  return ss.str();
}

}
