#include "Facade.h"

Facade::Facade(acc::LibFacadeInterface &lib) : m_table(lib.transaction(), m_builder) {
}

Builder &Facade::builder() { return m_builder; }
