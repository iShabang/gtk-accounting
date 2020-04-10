#include <gtk-accounting/LibFacade.h>

namespace acc {

LibFacade::LibFacade() {}

DatabaseInterface& LibFacade::database() { return m_database; }
DispatchInterface& LibFacade::dispatcher() { return m_dispatcher; }

}  // namespace acc
