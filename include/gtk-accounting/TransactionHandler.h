#ifndef _GTK_ACCOUNTING_TRANSACTION_HANDLER_H_
#define _GTK_ACCOUNTING_TRANSACTION_HANDLER_H_

#include <gtk-accounting/DatabaseInterface.h>
#include <gtk-accounting/DispatchInterface.h>
#include <gtk-accounting/TransactionInterface.h>

#include <unordered_map>
#include <utility>

namespace acc {

class TransactionHandler : public TransactionInterface {
 public:
  TransactionHandler(DatabaseInterface &database, DispatchInterface &dispatcher);

  ~TransactionHandler() = default;
  TransactionHandler(const TransactionHandler &) = delete;
  TransactionHandler(TransactionHandler &&) = delete;
  TransactionHandler &operator=(const TransactionHandler &) = delete;
  TransactionHandler &operator=(TransactionHandler &&) = delete;

 private:
  void addTransaction(const Transaction &transaction);
  void deleteSelected();
  void requestTransactions();
  void selectTransaction(const uint64_t &id, bool select);
  TransactionsReceived &transactionsReceived();
  InsertFailed &insertFailed();

  TransactionsReceived m_transactionsReceived;
  InsertFailed m_insertFailed;

 private:
  void addTransactionInternal(const Transaction &transaction);
  void requestTransactionsInternal();
  void deleteSelectedInternal();
  void selectTransactionInternal(const uint64_t &id, bool select);

 private:
  DatabaseInterface &m_database;
  DispatchInterface &m_dispatcher;

  std::unordered_map<uint64_t,bool> m_map;

};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_TRANSACTION_HANDLER_H_
