#ifndef _GTK_ACCOUNTING_SLOT_H_
#define _GTK_ACCOUNTING_SLOT_H_

#include <gtk-accounting/Functor.h>

namespace acc {

template <typename T>
class SlotBase {
 public:
  SlotBase(std::function<T> func) : m_functor(func) {}
  Functor<T> m_functor;
};

template <typename...>
class Slot;

template <>
class Slot<void()> : public SlotBase<void()> {
  using type = void();

 public:
  Slot(std::function<type> func) : SlotBase<type>(func) {}
  void operator()() { this->m_functor(); }
};

template <typename T1>
class Slot<void(T1)> : public SlotBase<void(T1)> {
  using type = void(T1);

 public:
  Slot(std::function<type> func) : SlotBase<type>(func) {}
  void operator()(T1 arg) { this->m_functor(arg); }
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_SLOT_H_
