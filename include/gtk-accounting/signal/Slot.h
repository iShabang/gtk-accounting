#ifndef _GTK_ACCOUNTING_SLOT_H_
#define _GTK_ACCOUNTING_SLOT_H_

#include <unordered_set>

#include "Functor.h"

namespace acc {

template <typename T>
class SlotBase {
 public:
  SlotBase(std::function<T> func, size_t id) : m_functor(func), m_id(id) {}
  Functor<T> m_functor;
  uint32_t m_id;
};

template <typename...>
class Slot;

template <typename T>
struct SlotHash {
  size_t operator()(const Slot<T> &slot) const { return std::hash<uint32_t>()(slot.m_id); }
};

template <typename T>
struct SlotCompare {
  bool operator()(const Slot<T> &slot1, const Slot<T> &slot2) const {
    return slot1.m_id == slot2.m_id;
  }
};

template <>
class Slot<void()> : public SlotBase<void()> {
  using type = void();

 public:
  Slot(std::function<type> func, size_t id) : SlotBase<type>(func, id) {}
  void operator()() const { this->m_functor(); }
};

template <typename T1>
class Slot<void(T1)> : public SlotBase<void(T1)> {
  using type = void(T1);

 public:
  Slot(std::function<type> func, size_t id) : SlotBase<type>(func, id) {}
  void operator()(T1 arg) const { this->m_functor(arg); }
};

template <typename T>
class SlotList {
 private:
  using hash_func = SlotHash<T>;
  using comp_func = SlotCompare<T>;
  using list_type = std::unordered_set<Slot<T>, hash_func, comp_func>;
  using slot_iter = typename list_type::iterator;
  using slot_const_iter = typename list_type::const_iterator;

 public:
  using iterator = slot_iter;
  using const_iterator = slot_const_iter;
  void insert(Slot<T> slot) { m_slots.insert(slot); }
  void erase(Slot<T> slot) { m_slots.erase(slot); }
  slot_iter begin() { return m_slots.begin(); }
  slot_iter end() { return m_slots.end(); }

 private:
  list_type m_slots;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_SLOT_H_
