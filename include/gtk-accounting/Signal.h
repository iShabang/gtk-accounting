#ifndef _GTK_ACCOUNTING_SIGNAL_H_
#define _GTK_ACCOUNTING_SIGNAL_H_

#include <list>

#include <gtk-accounting/Slot.h>

namespace acc {

template <typename T>
class SignalBase {
 public:
  void connect(std::function<T> func) { m_slots.push_back(func); }

  std::list<Slot<T>> m_slots;
};

template <typename...>
class Signal;

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

}  // namespace acc

#endif  //  _GTK_ACCOUNTING_SIGNAL_H_
