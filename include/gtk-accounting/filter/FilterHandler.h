#ifndef _GTK_ACCOUNTING_FILTER_HANDLER_H_
#define _GTK_ACCOUNTING_FILTER_HANDLER_H_

#include <gtk-accounting/dispatch/DispatchInterface.h>
#include <gtk-accounting/filter/FilterInterface.h>
#include <gtk-accounting/filter/FilterParser.h>
#include <gtk-accounting/filter/FilterWriter.h>
#include <gtk-accounting/log/LogChannel.h>
#include <gtk-accounting/misc/Result.h>

#include <map>
#include <vector>

namespace acc
{
class FilterHandler : public FilterInterface
{
 public:
  FilterHandler(DispatchInterface &dispatcher, FilterParser &parser);

  ~FilterHandler() = default;
  FilterHandler(const FilterHandler &) = delete;
  FilterHandler(FilterHandler &&) = delete;
  FilterHandler &operator=(const FilterHandler &) = delete;
  FilterHandler &operator=(FilterHandler &&) = delete;

 private:
  void addFilter(const Filter &filter);
  void deleteFilter(uint16_t id);
  void selectFilter(uint16_t id);

  void addFilterInternal(const Filter &filter);
  void deleteFilterInternal(uint16_t id);
  void selectFilterInternal(uint16_t id);

 private:
  void onFiltersParsed(const std::vector<Filter> &filters);
  void writeFilters();

 private:
  DispatchInterface &m_dispatcher;
  LogChannel m_log;

  uint16_t m_currentId;
  std::map<uint16_t, Filter> m_filters;
  uint16_t m_selected;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_FILTER_HANDLER_H_
