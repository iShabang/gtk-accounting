#ifndef _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_
#define _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_

#include <gtk-accounting/Transaction.h>
#include <gtk-accounting/Signal.h>

#include <vector>

namespace acc {
class TransactionInterface {
public:
  virtual ~TransactionInterface() {}

  using TransactionsReceived = Signal<void(std::vector<acc::Transaction>)>;
  using InsertFailed = Signal<void()>;

  virtual void addTransaction(const Transaction &transaction) = 0;
  virtual void deleteSelected() = 0;
  virtual void requestTransactions() = 0;
  virtual void selectTransaction(const uint64_t &id, bool select) = 0;
  virtual TransactionsReceived &transactionsReceived() = 0;
  virtual InsertFailed &insertFailed() = 0;
};
} // namespace acc

#endif // _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_
