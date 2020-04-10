#ifndef _GTK_ACCOUNTING_LIB_FACADE_H_
#define _GTK_ACCOUNTING_LIB_FACADE_H_

#include <gtk-accounting/MainDispatcher.h>
#include <gtk-accounting/SqliteImplementation.h>

namespace acc {

class LibFacade {
 public:
  LibFacade();

  ~LibFacade() = default;
  LibFacade(const LibFacade &) = delete;
  LibFacade(LibFacade &&) = delete;
  LibFacade &operator=(const LibFacade &) = delete;
  LibFacade &operator=(LibFacade &&) = delete;

  DatabaseInterface &database();
  DispatchInterface &dispatcher();

 private:
  MainDispatcher m_dispatcher;
  SqliteImplementation m_database;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_LIB_FACADE_H_
