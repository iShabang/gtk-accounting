#include "Facade.h"

Facade::Facade(acc::LibFacadeInterface &lib)
    : m_table(lib.transaction(), m_builder),
      m_addTranPopup(lib.transaction()),
      m_menuBox(lib.transaction(), m_builder, m_addTranPopup, m_filterWindow),
      m_infoBox(m_builder, lib.transaction())
{
}

Builder &Facade::builder() { return m_builder; }
