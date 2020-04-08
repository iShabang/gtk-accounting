#ifndef _GTK_ACCOUNTING_LIB_FACADE_H_
#define _GTK_ACCOUNTING_LIB_FACADE_H_

#include <gtk-accounting/SqliteImplementation.h>

namespace acc {

class LibFacade {

  public:
  LibFacade();

  ~LibFacade() = default;
  LibFacade(const LibFacade &) = delete;
  LibFacade(LibFacade &&) = delete;
  LibFacade& operator=(const LibFacade &) = delete;
  LibFacade& operator=(LibFacade &&) = delete;

  private:
  SqliteImplementation m_database;

};

}

#endif // _GTK_ACCOUNTING_LIB_FACADE_H_
