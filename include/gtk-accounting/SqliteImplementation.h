#ifndef _GTK_ACCOUNTING_SQLITE_IMPLEMENTATION_H_
#define _GTK_ACCOUNTING_SQLITE_IMPLEMENTATION_H_

#include <gtk-accounting/DatabaseInterface.h>

#include <sqlite3.h>

namespace acc {

class SqliteImplementation : public DatabaseInterface {
public:
  SqliteImplementation();

  ~SqliteImplementation() = default;
  SqliteImplementation(const SqliteImplementation &) = delete;
  SqliteImplementation(SqliteImplementation &&) = delete;
  SqliteImplementation &operator=(const SqliteImplementation &) = delete;
  SqliteImplementation &operator=(SqliteImplementation &&) = delete;

private:
  bool isOpen() const;
  Result<DatabaseResult<Transaction>, std::string> queryTransactions();
  bool insertTransactions(std::vector<Transaction>);

  std::string getQuery();
  void createTables();

private:
  sqlite3 *m_db;
  bool m_isOpen;
};
} // namespace acc

#endif // _GTK_ACCOUNTING_SQLITE_IMPLEMENTATION_H_
