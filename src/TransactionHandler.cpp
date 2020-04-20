#include <gtk-accounting/TransactionHandler.h>

#include <iostream>

namespace acc {

TransactionHandler::TransactionHandler(DatabaseInterface &database, DispatchInterface &dispatcher)
    : m_database(database), m_dispatcher(dispatcher), m_logger("TransactionHandler") {}

void TransactionHandler::addTransaction(const Transaction &transaction) {
  m_dispatcher.queueEvent([this, &transaction]() { addTransactionInternal(transaction); });
}

void TransactionHandler::addTransactionInternal(const Transaction &transaction) {
  if (!m_database.insertTransactions({transaction})) {
    m_insertFailed();
  }
}

void TransactionHandler::deleteSelected() {
  m_dispatcher.queueEvent([this]() { deleteSelected(); });
}

void TransactionHandler::deleteSelectedInternal() {
  std::vector<uint64_t> selected;
  for (auto &&i : m_map) {
    if (i.second) {
      selected.push_back(i.first);
    }
  }
  m_database.deleteTransactions(selected);
}

void TransactionHandler::requestTransactions() {
  m_dispatcher.queueEvent([this]() { requestTransactionsInternal(); });
}

void TransactionHandler::requestTransactionsInternal() {
  Result<DatabaseResult<Transaction>, std::string> result = m_database.queryTransactions();
  if (result.success()) {
    m_transactionsReceived(result.object());
    m_map.clear();
    for (auto &&i : result.object()) {
      m_map[i.id] = false;
    }
  } else {
    std::cerr << "TransactionHandler::requestTransactions(): Database error: " << result.error()
              << "\n";
  }
}

void TransactionHandler::selectTransaction(const uint64_t &id, bool select) {
  m_dispatcher.queueEvent([this, &id, &select]() { selectTransactionInternal(id, select); });
}

void TransactionHandler::selectTransactionInternal(const uint64_t &id, bool select) {
  LOG(DEBUG,m_logger) << "selectTransactionInternal(): id: " << id << " select: " << select;
  auto entry = m_map.find(id);
  if (entry != m_map.end()) {
    m_map[id] = select;
  }
}

TransactionInterface::TransactionsReceived &TransactionHandler::transactionsReceived() {
  return m_transactionsReceived;
}

TransactionInterface::InsertFailed &TransactionHandler::insertFailed() { return m_insertFailed; }

}  // namespace acc
