#ifndef _GTK_ACCOUNTING_LOG_DISPATCHER_H_
#define _GTK_ACCOUNTING_LOG_DISPATCHER_H_

#include <gtk-accounting/dispatch/MainDispatcher.h>

namespace acc {

class LogDispatcher {
 private:
  static LogDispatcher instance;
  LogDispatcher();
  void printMessge(const std::string &message);

 public:
  static LogDispatcher &getInstance(); 
  void queueMessage(const std::string &message);

  LogDispatcher(const LogDispatcher &) = delete;
  LogDispatcher(LogDispatcher &&) = delete;
  LogDispatcher& operator=(const LogDispatcher &) = delete;
  LogDispatcher& operator=(LogDispatcher &&) = delete;

 private:
  MainDispatcher m_dispatcherImpl;
  DispatchInterface &m_dispatcher;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_LOG_DISPATCHER_H_
