#include <gtk-accounting/facade/LibFacade.h>

namespace acc
{
const std::string FILTER_PATH = "filters.xml";

LibFacade::LibFacade()
    : m_filterParser(m_dispatcher, FILTER_PATH),
      m_filterHandler(m_dispatcher, m_filterParser),
      m_database(m_filterHandler),
      m_transactions(m_database, m_dispatcher)
{
}

DatabaseInterface& LibFacade::database() { return m_database; }
DispatchInterface& LibFacade::dispatcher() { return m_dispatcher; }
FilterInterface& LibFacade::filter() { return m_filterHandler; }
TransactionInterface& LibFacade::transaction() { return m_transactions; }

}  // namespace acc
