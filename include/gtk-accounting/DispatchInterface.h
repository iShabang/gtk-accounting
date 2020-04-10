#ifndef _GTK_ACCOUNTING_DISPATCH_INTERFACE_H_
#define _GTK_ACCOUNTING_DISPATCH_INTERFACE_H_

#include <functional>

namespace acc {
class DispatchInterface {
  public:
  virtual ~DispatchInterface() {}

  using DispatchEvent = std::function<void(void)>; 

  virtual void queueEvent(DispatchEvent) = 0;
};
}  // namespace acc

#endif  // _GTK_ACCOUNTING_DISPATCH_INTERFACE_H_
