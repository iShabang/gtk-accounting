#ifndef _GTK_ACCOUNTING_PRECISION_H_
#define _GTK_ACCOUNTING_PRECISION_H_

#include <string>

namespace acc {

  /* Converts a double value into a string with two decimal point precision.
   * Since the application is showing monetary values, this method is used
   * to conveniently display them with the correct precision */
  std::string doubleToString(const double &value);

}

#endif // _GTK_ACCOUNTING_PRECISION_H_
