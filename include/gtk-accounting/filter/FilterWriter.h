#ifndef _GTK_ACCOUNTING_FILTER_WRITER_H_
#define _GTK_ACCOUNTING_FILTER_WRITER_H_

#include <gtk-accounting/filter/Filter.h>
#include <gtk-accounting/log/LogChannel.h>

#include <fstream>
#include <string>
#include <vector>

namespace acc
{
class FilterWriter
{
 public:
  FilterWriter();

  FilterWriter(const FilterWriter &) = delete;
  FilterWriter(FilterWriter &&) = delete;
  FilterWriter &operator=(const FilterWriter &) = delete;
  FilterWriter &operator=(FilterWriter &&) = delete;

  void write(const std::string &path, std::vector<Filter> &filters);

  void writeHeader();
  void writeDate(const Filter &filter);
  void writeAmount(const Filter &filter);
  void writeNumeric(const std::string &tag, const std::string &min, const std::string &max);
  void writeGeneric(const std::string &tag, const std::string &val);
  void writePattern(const Filter &filter);
  void writeMin(const std::string &val);
  void writeMax(const std::string &val);

 private:
  std::ofstream m_os;
  LogChannel m_log;
};
}  // namespace acc

#endif  // _GTK_ACCOUNTING_FILTER_WRITER_H_
