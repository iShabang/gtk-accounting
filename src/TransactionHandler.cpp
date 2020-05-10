#include <gtk-accounting/Time.h>
#include <gtk-accounting/TransactionHandler.h>

namespace acc
{
TransactionHandler::TransactionHandler(DatabaseInterface &database, DispatchInterface &dispatcher)
    : m_database(database), m_dispatcher(dispatcher), m_logger("TransactionHandler"), m_map(0)
{
}

void TransactionHandler::addTransaction(const Transaction &transaction)
{
  m_dispatcher.queueEvent([this, &transaction]() { addTransactionInternal(transaction); });
}

void TransactionHandler::addTransactionInternal(const Transaction &transaction)
{
  DateResult result = stringToDate(transaction.date);
  if (result.success())
  {
    Date date = result.object();
    int dayLimit = getMonthDayCount(date.month, date.year);
    LOG(DEBUG, m_logger) << "addTransactionInternal(): dayLimit: " << dayLimit
                         << ", day: " << date.day;
    if (date.day > dayLimit)
    {
      m_invalidData(DATE);
      return;
    }
  }

  if (m_database.insertTransactions({transaction}))
  {
    m_insertSuccess();
  }
  else
  {
    m_insertFailed();
  }
}

void TransactionHandler::deleteSelected()
{
  m_dispatcher.queueEvent([this]() { deleteSelectedInternal(); });
}

void TransactionHandler::deleteSelectedInternal()
{
  LOG(DEBUG, m_logger) << "deleteSelectedInternal(): entry";
  std::vector<uint64_t> selected;
  for (auto &&i : m_map)
  {
    if (i.second)
    {
      LOG(DEBUG, m_logger) << "deleteSelectedInternal(): Deleting id: " << i.first;
      selected.push_back(i.first);
    }
  }
  m_database.deleteTransactions(selected);
}

void TransactionHandler::requestTransactions()
{
  m_dispatcher.queueEvent([this]() { requestTransactionsInternal(); });
}

void TransactionHandler::requestTransactionsInternal()
{
  Result<DatabaseResult<Transaction>, std::string> result = m_database.queryTransactions();
  if (result.success())
  {
    m_map.clear();
    double sum = sumValues(result.object());
    m_currentTotal(sum);
    m_transactionsReceived(result.object());
  }
  else
  {
    LOG(DEBUG, m_logger) << "requestTransactions(): Database error: " << result.error() << "\n";
  }
}

void TransactionHandler::selectTransaction(const uint64_t &id, bool select)
{
  m_dispatcher.queueEvent([this, id, select]() { selectTransactionInternal(id, select); });
}

void TransactionHandler::selectTransactionInternal(const uint64_t &id, bool select)
{
  LOG(DEBUG, m_logger) << "selectTransactionInternal(): id: " << id << " select: " << select;
  m_map[id] = select;
}

double TransactionHandler::sumValues(const std::vector<Transaction> &data)
{
  double sum = 0;
  for (auto &&i : data)
  {
    sum += i.amount;
  }
  return sum;
}

TransactionInterface::TransactionsReceived &TransactionHandler::transactionsReceived()
{
  return m_transactionsReceived;
}

TransactionInterface::InsertFailed &TransactionHandler::insertFailed() { return m_insertFailed; }

TransactionInterface::InsertSuccess &TransactionHandler::insertSuccess() { return m_insertSuccess; }

TransactionInterface::InvalidData &TransactionHandler::invalidData() { return m_invalidData; }

TransactionInterface::CurrentTotal &TransactionHandler::currentTotal() { return m_currentTotal; }

}  // namespace acc
