#ifndef _GTK_ACCOUNTING_LIB_FACADE_INTERFACE_H_
#define _GTK_ACCOUNTING_LIB_FACADE_INTERFACE_H_

#include <gtk-accounting/DatabaseInterface.h>
#include <gtk-accounting/DispatchInterface.h>
#include <gtk-accounting/TransactionInterface.h>

namespace acc {
class LibFacadeInterface {
 public:
  virtual ~LibFacadeInterface() {}

  virtual DatabaseInterface &database() = 0;
  virtual DispatchInterface &dispatcher() = 0;
  virtual TransactionInterface &transaction() = 0;
};
}  // namespace acc

#endif  // _GTK_ACCOUNTING_LIB_FACADE_INTERFACE_H_
