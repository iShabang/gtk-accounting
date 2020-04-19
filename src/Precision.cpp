#include <gtk-accounting/Precision.h>
#include <sstream>
#include <iomanip>

namespace acc {

  std::string floatToString(const float &value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
  }

}
