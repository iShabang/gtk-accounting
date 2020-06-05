#include <gtk-accounting/filter/FilterWriter.h>

namespace acc
{
FilterWriter::FilterWriter() : m_log("FilterWriter") {}

void FilterWriter::write(const std::string &path, std::vector<Filter> &filters)
{
  m_os.open(path);
  if (!m_os)
  {
    LOG(DEBUG, m_log) << "write(): Failed to open " << path << " for writing";
    return;
  }

  writeHeader();

  m_os << "<Root>\n";

  for (auto &&i : filters)
  {
    m_os << "<Filter name=\"" << i.name << "\">\n";

    if (i.dateMin.length() || i.dateMax.length()) writeDate(i);


    if (i.amountMin.length() || i.amountMax.length()) writeAmount(i);

    if (i.pattern.length()) writePattern(i);

    m_os << "</Filter>\n";
  }

  m_os << "</Root>\n";
  m_os.close();
}

void FilterWriter::writeHeader() { m_os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"; }

void FilterWriter::writeDate(const Filter &filter)
{
  writeNumeric("Date", filter.dateMin, filter.dateMax);
}

void FilterWriter::writeAmount(const Filter &filter)
{
  writeNumeric("Amount", filter.amountMin, filter.amountMax);
}

void FilterWriter::writePattern(const Filter &filter) { writeGeneric("Pattern", filter.pattern); }

void FilterWriter::writeMin(const std::string &val) { writeGeneric("Min", val); }

void FilterWriter::writeMax(const std::string &val) { writeGeneric("Max", val); }

void FilterWriter::writeNumeric(const std::string &tag, const std::string &min,
                                const std::string &max)
{
  m_os << "<" << tag << ">\n";
  if (min.length()) writeMin(min);
  if (max.length()) writeMax(max);
  m_os << "</" << tag << ">\n";
}

void FilterWriter::writeGeneric(const std::string &tag, const std::string &val)
{
  m_os << "<" << tag << ">" << val << "</" << tag << ">\n";
}

}  // namespace acc
