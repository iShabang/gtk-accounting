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
    SqliteImplementation& operator=(const SqliteImplementation &) = delete;
    SqliteImplementation& operator=(SqliteImplementation &&) = delete;

    private:
    Result<DatabaseResult<Transaction>,std::string> queryTransactions();

    std::string getQuery();

    private:
    sqlite3* m_db;
  };
}

#endif // _GTK_ACCOUNTING_SQLITE_IMPLEMENTATION_H_
