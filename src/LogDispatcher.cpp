#include <gtk-accounting/LogDispatcher.h>

#include <iostream>

namespace acc {

  LogDispatcher LogDispatcher::instance = LogDispatcher();

  LogDispatcher::LogDispatcher() : m_dispatcher(m_dispatcherImpl) {}

  LogDispatcher &LogDispatcher::getInstance() { return instance; }

  void LogDispatcher::queueMessage(const std::string &message) {
    m_dispatcher.queueEvent([this, message](){ printMessge(message); });
  }

  void LogDispatcher::printMessge(const std::string &message) 
  {
    std::cerr << message << "\n";
  }
}
