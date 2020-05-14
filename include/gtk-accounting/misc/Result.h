#ifndef _GTK_ACCOUNTING_RESULT_H_
#define _GTK_ACCOUNTING_RESULT_H_

#include <utility>

namespace acc {

  /* Class used to wrap function return values in a way that provides more
   * information on any failures that occur. Typically the error type will be
   * a string that can be directly logged */
  template <typename R, typename E>
  class Result {
    public:
    Result() : m_success(false) {}

    /* Retrieves the object */
    R&& object() { return std::move(m_object); }

    /* Retrieves the error */
    E&& error() { return std::move(m_error); }

    /* Test of the operation was successfull */
    bool success() { return m_success; }

    /* Mark operation as unsuccessfull and provide error information */
    void setError(E&& error) {
      m_success = false;
      m_error = std::move(error);
    }

    /* Mark operation as successfull and provide the result object */
    void setSuccess(R&& object) {
      m_success = true;
      m_object = std::move(object);
    }

    private:
    R m_object;
    E m_error;
    bool m_success;
  };
}

#endif // _GTK_ACCOUNTING_RESULT_H_
