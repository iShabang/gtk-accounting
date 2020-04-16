#ifndef _SIGNALS_CONNECTION_H_
#define _SIGNALS_CONNECTION_H_

#include "Slot.h"
#include <memory>

template <typename T> class Connection {
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
    ScopedConnection(Connection<T> &conn) : destructor([&conn](){ conn.disconnect(); }) {}

    template <typename T>
    ScopedConnection(std::shared_ptr<Connection<T>> conn) : destructor([conn](){ conn->disconnect(); }) {}

    ~ScopedConnection() { destructor(); }
  private:
    std::function<void()> destructor;

};

#endif // _SIGNALS_CONNECTION_H_
