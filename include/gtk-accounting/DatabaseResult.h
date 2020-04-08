#ifndef _GTK_ACCOUNTING_DATABASE_RESULT_H_
#define _GTK_ACCOUNTING_DATABASE_RESULT_H_

#include <gtk-accounting/Transaction.h>

#include <vector>

namespace acc {

template <typename T> using DatabaseResult = std::vector<T>;

}

#endif // _GTK_ACCOUNTING_DATABASE_RESULT_H_
