#ifndef _GTK_ACCOUNTING_TRANSACTION_H_
#define _GTK_ACCOUNTING_TRANSACTION_H_

#include <string>
#include <cstdint>

namespace acc {
  /* Transaction object used to store information about the transaction itself */
  struct Transaction {
    uint64_t id;
    std::string name;
    std::string date; // date format in YYYY-MM-DD
    double amount;
  };
}

#endif // _GTK_ACCOUNTING_TRANSACTION_H_
