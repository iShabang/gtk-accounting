#ifndef _GTK_ACCOUNTING_DATABASE_INTERFACE_H_
#define _GTK_ACCOUNTING_DATABASE_INTERFACE_H_

#include <gtk-accounting/DatabaseResult.h>
#include <gtk-accounting/Result.h>

#include <functional>
#include <string>
#include <vector>

namespace acc {

class DatabaseInterface {
  public:
  virtual ~DatabaseInterface() {}

  virtual Result<DatabaseResult<Transaction>,std::string> queryTransactions() = 0;
};

}

#endif // _GTK_ACCOUNTING_DATABASE_INTERFACE_H_
