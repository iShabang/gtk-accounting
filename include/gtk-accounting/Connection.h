#ifndef _GTK_ACCOUNTING_CONNECTION_H_
#define _GTK_ACCOUNTING_CONNECTION_H_

#include <memory>

#include "Slot.h"

namespace acc {

template <typename T>
class Connection {
  using slot_type = Slot<T>;
  using disconnect_func = std::function<void(slot_type)>;

 public:
  Connection(slot_type slot, disconnect_func func) : m_slot(slot), m_disconnectFunc(func) {}
  void disconnect() { m_disconnectFunc(m_slot); }
  bool connected() {
    if (m_disconnectFunc) {
      return true;
    }
    return false;
  }

 private:
  slot_type m_slot;
  disconnect_func m_disconnectFunc;
};

class ScopedConnection {
 public:
  template <typename T>
  ScopedConnection(Connection<T> &conn) : destructor([&conn]() { conn.disconnect(); }) {}

  template <typename T>
  ScopedConnection(std::shared_ptr<Connection<T>> conn)
      : destructor([conn]() { conn->disconnect(); }) {}

  ~ScopedConnection() { destructor(); }

 private:
  std::function<void()> destructor;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_CONNECTION_H_
