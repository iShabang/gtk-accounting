#include <gtk-accounting/LibFacade.h>

namespace acc {

LibFacade::LibFacade() {}

DatabaseInterface& LibFacade::database() { return m_database; }

}
