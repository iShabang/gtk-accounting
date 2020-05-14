#ifndef _GTK_ACCOUNTING_RESULT_H_
#define _GTK_ACCOUNTING_RESULT_H_

#include <utility>

namespace acc {
  template <typename R, typename E>
  class Result {
    public:
    Result() : m_success(false) {}
    R&& object() { return std::move(m_object); }
    E&& error() { return std::move(m_error); }
    bool success() { return m_success; }
    void setError(E&& error) {
      m_success = false;
      m_error = std::move(error);
    }
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
