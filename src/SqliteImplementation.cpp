#include <gtk-accounting/SqliteImplementation.h>

#include <iostream>
#include <sstream>

namespace acc {

SqliteImplementation::SqliteImplementation() {

  if (sqlite3_open("gtk-accounting.db", &m_db) != SQLITE_OK)
    std::cerr << "SqliteImplementation::SqliteImplementation(): Error opening database\n";
}

Result<DatabaseResult<Transaction>,std::string> SqliteImplementation::queryTransactions() {
  Result<DatabaseResult<Transaction>,std::string> result;
  sqlite3_stmt *statement = nullptr;
  std::string queryString = getQuery();
  int resultCode = sqlite3_prepare_v2(m_db,queryString.c_str(),queryString.length(),&statement,nullptr);
  if (resultCode == SQLITE_OK) {
    DatabaseResult<Transaction> transactions;
    int stepCode = sqlite3_step(statement);
    while(stepCode == SQLITE_ROW) {
      uint8_t index = 0;
      Transaction newTrans;
      newTrans.id = sqlite3_column_int64(statement,index++);
      newTrans.name = reinterpret_cast<const char *>(sqlite3_column_text(statement,index++));
      newTrans.date = reinterpret_cast<const char *>(sqlite3_column_text(statement,index++));
      newTrans.amount = sqlite3_column_double(statement,index);
      transactions.push_back(newTrans);
    }
    result.setSuccess(std::move(transactions));
  } else {
    std::stringstream ss;
    ss << "SqliteImplementation: Failed to retrieve transactions. Sqlite Result Code: " << resultCode;
    result.setError(ss.str());
  }

  sqlite3_finalize(statement);

  return result;
}

std::string SqliteImplementation::getQuery()
{
  //TODO
  std::string query;
  return query;
}

} // namespace acc
