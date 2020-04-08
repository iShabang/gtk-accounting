#ifndef _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_
#define _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_

#include <gtk-accounting/Transaction.h>

#include <vector>
#include <sigc++/signal.h>

namespace acc {
class TransactionInterface {
public:
  virtual ~TransactionInterface() {}

  using TransactionsReceived = sigc::signal<void(std::vector<Transaction>)>;

  virtual void addTransaction(const Transaction &transaction) = 0;
  virtual void deleteTransaction(const uint64_t &id) = 0;
  virtual void requestTransactions() = 0;
  virtual TransactionsReceived &transactionsReceived() = 0;
};
} // namespace acc

#endif // _GTK_ACCOUNTING_TRANSACTION_INTERFACE_H_
