#ifndef _GTK_ACCOUNTING_FUNCTOR_H_
#define _GTK_ACCOUNTING_FUNCTOR_H_

#include <functional>

namespace acc {

template <typename T>
class FunctorBase {
 public:
  FunctorBase(std::function<T> func) : m_function(func) {}
  std::function<T> m_function;
};

template <typename...>
class Functor;

template <>
class Functor<void()> : public FunctorBase<void()> {
  using sig = void();

 public:
  Functor(std::function<sig> func) : FunctorBase<sig>(func) {}
  void operator()() { this->m_function(); }
};

template <typename T1>
class Functor<void(T1)> : public FunctorBase<void(T1)> {
  using sig = void(T1);

 public:
  Functor(std::function<sig> func) : FunctorBase<sig>(func) {}
  void operator()(T1 arg1) { this->m_function(arg1); }
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_FUNCTOR_H_
