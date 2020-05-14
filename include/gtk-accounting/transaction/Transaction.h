#ifndef _GTK_ACCOUNTING_TRANSACTION_H_
#define _GTK_ACCOUNTING_TRANSACTION_H_

#include <string>
#include <cstdint>

namespace acc {
  struct Transaction {
    uint64_t id;
    std::string name;
    std::string date;
    double amount;
  };
}

#endif // _GTK_ACCOUNTING_TRANSACTION_H_
