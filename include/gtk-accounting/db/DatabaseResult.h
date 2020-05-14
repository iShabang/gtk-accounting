#ifndef _GTK_ACCOUNTING_DATABASE_RESULT_H_
#define _GTK_ACCOUNTING_DATABASE_RESULT_H_

#include <gtk-accounting/transaction/Transaction.h>

#include <vector>

namespace acc {

/* Simple name definition used in case the result container needs to be changed in the future */
template <typename T> using DatabaseResult = std::vector<T>;

}

#endif // _GTK_ACCOUNTING_DATABASE_RESULT_H_
