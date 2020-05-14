#ifndef _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_
#define _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_

#include <gtk-accounting/signal/Signal.h>
#include <gtk-accounting/transaction/Transaction.h>

#include <vector>

namespace acc
{

/* Interface used to provide transaction informatino and functionality to the GUI. */
class TransactionInterface
{
 public:
  virtual ~TransactionInterface() {}

  enum DataError
  {
    NAME,
    DATE,
    AMOUNT
  };

  /* Signal containing the requested transactions to be displayed by the GUI */
  using TransactionsReceived = Signal<void(std::vector<acc::Transaction>)>;

  /* Signal indicating the request to insert failed */
  using InsertFailed = Signal<void()>;

  /* Signal indicating the request to insert succeeded */
  using InsertSuccess = Signal<void()>;

  /* Signal indicating the last request contained invalid data 
   * Carries information indicating what aspect of the data was invalid */
  using InvalidData = Signal<void(DataError)>;

  /* Signal carrying the total of the current list of transactions */
  using CurrentTotal = Signal<void(double)>;

  /* Store the passed transaction */
  virtual void addTransaction(const Transaction &transaction) = 0;

  /* Delete all user selected transactions */
  virtual void deleteSelected() = 0;

  /* Request transactions to be displayed */
  virtual void requestTransactions() = 0;

  /* Select/Unselect transaction by ID 
   * if select is true, the transaction is selected
   * if select is false, the transaction is deselected */
  virtual void selectTransaction(const uint64_t &id, bool select) = 0;

  // Signal getters
  virtual TransactionsReceived &transactionsReceived() = 0;
  virtual InsertFailed &insertFailed() = 0;
  virtual InsertSuccess &insertSuccess() = 0;
  virtual InvalidData &invalidData() = 0;
  virtual CurrentTotal &currentTotal() = 0;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_
