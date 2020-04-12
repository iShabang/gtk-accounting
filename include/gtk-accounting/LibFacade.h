#ifndef _GTK_ACCOUNTING_LIB_FACADE_H_
#define _GTK_ACCOUNTING_LIB_FACADE_H_

#include <gtk-accounting/LibFacadeInterface.h>
#include <gtk-accounting/MainDispatcher.h>
#include <gtk-accounting/SqliteImplementation.h>
#include <gtk-accounting/TransactionHandler.h>

namespace acc {

class LibFacade : public LibFacadeInterface {
 public:
  LibFacade();

  ~LibFacade() = default;
  LibFacade(const LibFacade &) = delete;
  LibFacade(LibFacade &&) = delete;
  LibFacade &operator=(const LibFacade &) = delete;
  LibFacade &operator=(LibFacade &&) = delete;

 private:
  DatabaseInterface &database();
  DispatchInterface &dispatcher();
  TransactionInterface &transaction();

 private:
  MainDispatcher m_dispatcher;
  SqliteImplementation m_database;
  TransactionHandler m_transactions;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_LIB_FACADE_H_
