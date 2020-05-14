#ifndef _GTK_ACCOUNTING_LIB_FACADE_INTERFACE_H_
#define _GTK_ACCOUNTING_LIB_FACADE_INTERFACE_H_

#include <gtk-accounting/db/DatabaseInterface.h>
#include <gtk-accounting/dispatch/DispatchInterface.h>
#include <gtk-accounting/transaction/TransactionInterface.h>

namespace acc {

/* Interface for external applications to access running library interfaces */
class LibFacadeInterface {
 public:
  virtual ~LibFacadeInterface() {}

  virtual DatabaseInterface &database() = 0;
  virtual DispatchInterface &dispatcher() = 0;
  virtual TransactionInterface &transaction() = 0;
};
}  // namespace acc

#endif  // _GTK_ACCOUNTING_LIB_FACADE_INTERFACE_H_
