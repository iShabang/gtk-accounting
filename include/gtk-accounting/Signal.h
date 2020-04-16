#ifndef _SIGNALS_SIGNAL_H_
#define _SIGNALS_SIGNAL_H_

#include "Connection.h"
#include "Slot.h"
#include <list>
#include <memory>

template <typename T>
class SignalBase {
  using conn_ptr = std::shared_ptr<Connection<T>>;
  public:
    SignalBase() : listCount(0) {}
    conn_ptr connect(std::function<T> func) {
      auto slot = Slot<T>(func,++listCount);
      m_slots.insert(slot);
      return conn_ptr( new Connection<T>(slot, [this](const Slot<T> &slot) { m_slots.erase(slot); }));
    }
    SlotList<T> m_slots;
    uint32_t listCount;
};

template <typename ...> class Signal;

template <>
class Signal<void()> : public SignalBase<void()> {
  using type = void();
  public:
    void operator()() {
      for (auto &&i : this->m_slots) {
        i();
      }
    }
};

template <typename T1>
class Signal<void(T1)> : public SignalBase<void(T1)> {
  using type = void(T1);
  public:
    void operator()(T1 arg) {
      for (auto &&i : this->m_slots) {
        i(arg);
      }
    }
};

#endif // _SIGNALS_SIGNAL_H_
