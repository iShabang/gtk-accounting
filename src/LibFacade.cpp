#include <gtk-accounting/facade/LibFacade.h>

namespace acc
{
LibFacade::LibFacade() : m_transactions(m_database, m_dispatcher), m_filterParser(m_dispatcher) {}

DatabaseInterface& LibFacade::database() { return m_database; }
DispatchInterface& LibFacade::dispatcher() { return m_dispatcher; }
TransactionInterface& LibFacade::transaction() { return m_transactions; }

}  // namespace acc
