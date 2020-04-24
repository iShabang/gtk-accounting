#include <gtk-accounting/SqliteImplementation.h>

#include <iostream>
#include <sstream>

namespace acc {

static const std::string DB_NAME = "gtk-accounting.db";

static const std::string TRANS_HEAD =
    "SELECT trans.id trans.name trans.date trans.amount FROM trans";
static const std::string DATE_SUFFIX = "WHERE date >= ? AND date <= ?";
static const std::string NAME_SUFFIX = "WHERE name LIKE ?";
static const std::string AMOUNT_SUFFIX = "WHERE amount >= ? AND amount <= ?";

SqliteImplementation::SqliteImplementation() : m_isOpen(false), m_log("SqliteImplementation") {
  int status = sqlite3_open_v2(DB_NAME.c_str(), &m_db, SQLITE_OPEN_READWRITE, nullptr);
  if (status == SQLITE_CANTOPEN) {
    int flags = 0;
    flags |= SQLITE_OPEN_READWRITE;
    flags |= SQLITE_OPEN_CREATE;
    status = sqlite3_open_v2(DB_NAME.c_str(), &m_db, flags, nullptr);
    if (status == SQLITE_OK) {
      std::cout << "SqliteImplementation::SqliteImplementation() creating tables" << std::endl;
      createTables();
    }
  }

  if (status == SQLITE_OK)
    m_isOpen = true;
  else
    std::cerr << "SqliteImplementation::SqliteImplementation(): Error code: " << status
              << " Message: " << sqlite3_errstr(status);
}

Result<DatabaseResult<Transaction>, std::string> SqliteImplementation::queryTransactions() {
  Result<DatabaseResult<Transaction>, std::string> result;
  sqlite3_stmt *statement = nullptr;
  std::string queryString = "SELECT * from trans";
  int resultCode =
      sqlite3_prepare_v2(m_db, queryString.c_str(), queryString.length(), &statement, nullptr);
  if (resultCode == SQLITE_OK) {
    DatabaseResult<Transaction> transactions;
    int stepCode = sqlite3_step(statement);
    while (stepCode == SQLITE_ROW) {
      uint8_t index = 0;
      Transaction newTrans;
      newTrans.id = sqlite3_column_int64(statement, index++);
      newTrans.name = reinterpret_cast<const char *>(sqlite3_column_text(statement, index++));
      newTrans.date = reinterpret_cast<const char *>(sqlite3_column_text(statement, index++));
      newTrans.amount = sqlite3_column_double(statement, index);
      transactions.push_back(newTrans);
      stepCode = sqlite3_step(statement);
    }
    result.setSuccess(std::move(transactions));
  } else {
    std::stringstream ss;
    ss << "SqliteImplementation: Failed to retrieve transactions. Sqlite "
          "Result Code: "
       << resultCode << " Message: " << sqlite3_errstr(resultCode);
    result.setError(ss.str());
  }

  sqlite3_finalize(statement);

  return result;
}

bool SqliteImplementation::isOpen() const { return m_isOpen; }

std::string SqliteImplementation::getQuery() {
  // TODO: Need filters to be implemented before querying the correct
  // information
  std::string query;
  return query;
}

bool SqliteImplementation::insertTransactions(std::vector<Transaction> transactions) {
  bool result = true;
  sqlite3_stmt *statement = nullptr;
  std::string queryString = "INSERT INTO trans(name, date, amount) VALUES (?,?,?);";
  int resultCode =
      sqlite3_prepare_v2(m_db, queryString.c_str(), queryString.length(), &statement, nullptr);
  if (resultCode == SQLITE_OK) {
    bool status = true;
    for (auto &&i : transactions) {
      status &=
          sqlite3_bind_text(statement, 1, i.name.c_str(), i.name.length(), nullptr) == SQLITE_OK;
      status &=
          sqlite3_bind_text(statement, 2, i.date.c_str(), i.date.length(), nullptr) == SQLITE_OK;
      status &= sqlite3_bind_double(statement, 3, i.amount) == SQLITE_OK;
      resultCode = sqlite3_step(statement);
      if (resultCode != SQLITE_DONE) {
        std::cerr << "SqliteImplementation::insertTransactions(): " << sqlite3_errstr(resultCode)
                  << ". Code: " << resultCode << "\n";
      }
      status &= resultCode == SQLITE_DONE;
      sqlite3_reset(statement);
    }
    result = status;
  } else
    result = false;
  return result;
}

void SqliteImplementation::createTables() {
  sqlite3_stmt *statement = nullptr;
  std::string queryString =
      "CREATE TABLE IF NOT EXISTS trans ("
      "id INTEGER PRIMARY KEY,"
      "name TEXT,"
      "date TEXT,"
      "amount REAL);";

  int resultCode =
      sqlite3_prepare_v2(m_db, queryString.c_str(), queryString.length(), &statement, nullptr);
  if (resultCode != SQLITE_OK)
    std::cerr << "SqliteImplementation::createTables(): Error: " << sqlite3_errstr(resultCode)
              << ". sqlite error code: " << resultCode << "\n";

  sqlite3_step(statement);

  sqlite3_finalize(statement);
}

bool SqliteImplementation::deleteTransactions(std::vector<uint64_t> ids) {
  LOG(DEBUG,m_log) << "deleteTransactions(): length: " << ids.size();
  std::string query = "DELETE FROM trans WHERE trans.id = ?";
  sqlite3_stmt *statement = nullptr;
  int res = sqlite3_prepare_v2(m_db, query.c_str(), query.length(), &statement, nullptr);

  if (res != SQLITE_OK) {
    LOG(ERROR, m_log) << "deleteTransactions(): Failed to prepare statement with error code: "
                      << res << ". Message: " << sqlite3_errstr(res);
    return false;
  }

  for (auto &&i : ids) {
    res = sqlite3_bind_int64(statement, 1, i);
    if (res != SQLITE_OK) {
      LOG(DEBUG, m_log) << "deleteSelectedInternal(): Failed to bind " << i
                        << " to delete statement. Error Code: " << res << ". Message: " << sqlite3_errstr(res);
      sqlite3_reset(statement);
      continue;
    }

    res = sqlite3_step(statement);

    if (res != SQLITE_DONE) {
      LOG(DEBUG, m_log) << "deleteSelectedInternal(): Failed to delete transaction with id " << i
                        << ". Error Code: " << res << ". Message: " << sqlite3_errstr(res);
    }

    sqlite3_reset(statement);
  }

  sqlite3_finalize(statement);

  LOG(DEBUG,m_log) << "deleteTransactions(): exit";

  return false;
}

}  // namespace acc
