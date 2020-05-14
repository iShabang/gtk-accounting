#ifndef _GTK_ACCOUNTING_DATABASE_INTERFACE_H_
#define _GTK_ACCOUNTING_DATABASE_INTERFACE_H_

#include <gtk-accounting/db/DatabaseResult.h>
#include <gtk-accounting/misc/Result.h>

#include <functional>
#include <string>
#include <vector>

namespace acc {

/* DatabaseInterface
 * Interface used to allow interactions between other library handlers and the database.
 * This is not intended for use by the GUI directly. This more so servers the purpose of
 * hiding the actual database implementation from the rest of the system.
 */
class DatabaseInterface {
  public:
  virtual ~DatabaseInterface() {}

  /* Test if the database connection is active
   * Return true if connection is active. False otherwise */
  virtual bool isOpen() const = 0;

  /* Retrieve transactions from the database.
   * Return data wrapped in a Result object to give the caller more information on any errors
   * that may have occurred. 
   * TODO: Add parameter for query information when filters are implemented
   */
  virtual Result<DatabaseResult<Transaction>,std::string> queryTransactions() = 0;

  /* Insert new transactions into the database
   * Returns true if successfull */
  virtual bool insertTransactions(std::vector<Transaction>) = 0;

  /* Remove transactions from the database using their unique IDs */
  virtual bool deleteTransactions(std::vector<uint64_t>) = 0;

};

}

#endif // _GTK_ACCOUNTING_DATABASE_INTERFACE_H_
