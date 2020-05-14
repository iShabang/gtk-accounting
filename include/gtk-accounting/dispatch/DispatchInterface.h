#ifndef _GTK_ACCOUNTING_DISPATCH_INTERFACE_H_
#define _GTK_ACCOUNTING_DISPATCH_INTERFACE_H_

#include <functional>

namespace acc {

/* Interface used to send events to the dispatch queue. */
class DispatchInterface {
  public:
  virtual ~DispatchInterface() {}
  
  /* All events will be void functions with no parameters. We can work around
   * this constraint using lambda functions that capture variables rather than 
   * add them to the functions argument list.
   *
   * Example:
   *
   * int x = 1;
   * int y = 2;
   *
   * queueEvent([this,&x,&y](){ someFunction(x,y); })
   *
   */
  using DispatchEvent = std::function<void(void)>; 

  /* Add an event to the dispatch queue */
  virtual void queueEvent(DispatchEvent) = 0;

  /* Shutdown the dispatch queue */
  virtual void shutdown() = 0;
};
}  // namespace acc

#endif  // _GTK_ACCOUNTING_DISPATCH_INTERFACE_H_
