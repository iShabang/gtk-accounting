#include <gtk-accounting/filter/FilterHandler.h>

namespace acc
{
FilterHandler::FilterHandler(DispatchInterface &dispatcher, FilterParser &parser)
    : m_dispatcher(dispatcher), m_log("FilterHandler"), m_currentId(0)
{
  parser.parse([this](const std::vector<Filter> &filters) { onFiltersParsed(filters); });
}

void FilterHandler::writeFilters()
{
  std::vector<Filter> temp;
  for (auto &&i : m_filters)
  {
    temp.push_back(i.second);
  }
  FilterWriter writer;
  writer.write("filters.xml", temp);
}

void FilterHandler::addFilter(const Filter &filter)
{
  m_dispatcher.queueEvent([this, filter]() { addFilterInternal(filter); });
}

void FilterHandler::deleteFilter(uint16_t id)
{
  m_dispatcher.queueEvent([this, id]() { deleteFilterInternal(id); });
}

void FilterHandler::selectFilter(uint16_t id)
{
  m_dispatcher.queueEvent([this, id]() { selectFilterInternal(id); });
}

void FilterHandler::requestFilters()
{
  m_dispatcher.queueEvent([this]() { requestFiltersInternal(); });
}

Filter FilterHandler::getSelected()
{
  if (m_selected)
    return m_filters.at(m_selected);
  else
    return Filter();
}

FilterHandler::FiltersReceived &FilterHandler::filtersReceived() { return m_filtersReceived; }
FilterHandler::Selected &FilterHandler::selected() { return m_selectedSignal; }
FilterHandler::NewFilter &FilterHandler::newFilter() { return m_newFilterSignal; }

void FilterHandler::addFilterInternal(const Filter &filter)
{
  m_filters[++m_currentId] = filter;
  writeFilters();
  m_newFilterSignal(m_currentId);
}

void FilterHandler::deleteFilterInternal(uint16_t id)
{
  m_filters.erase(id);
  writeFilters();
}

void FilterHandler::selectFilterInternal(uint16_t id)
{
  m_selected = id;
  m_selectedSignal();
}

void FilterHandler::requestFiltersInternal()
{
  std::vector<FilterSmall> filters;
  for (auto &&i : m_filters)
  {
    filters.push_back({i.first, i.second.name});
  }
  m_filtersReceived(filters);
}

void FilterHandler::onFiltersParsed(const std::vector<Filter> &filters)
{
  for (auto &&f : filters)
  {
    m_filters[++m_currentId] = f;
  }
}

}  // namespace acc
