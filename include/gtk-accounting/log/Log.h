#ifndef _GTK_ACCOUNTING_LOG_H_
#define _GTK_ACCOUNTING_LOG_H_

#include <gtk-accounting/log/LogDispatcher.h>

#include <sstream>


namespace acc {

enum LogLevel { DEBUG, WARNING, ERROR, CRITICAL };

class Log {
 public:
  Log() : logger(LogDispatcher::getInstance()) {}
  std::ostringstream &getStream(LogLevel level, const std::string &channelName) {
    std::string levelName;
    switch (level) {
      case DEBUG:
        levelName = "DEBUG";
        break;
      case WARNING:
        levelName = "WARNING";
        break;
      case ERROR:
        levelName = "ERROR";
        break;
      case CRITICAL:
        levelName = "CRITICAL";
        break;
    };

    os << levelName << " [" << channelName << "]: ";
    return os;
  }

  ~Log() {
    logger.queueMessage(os.str());
  }
  static LogLevel getLevel() {
#ifdef DEBUG_MODE
    return DEBUG;
#else
    return WARNING;
#endif
  }

 private:
  std::ostringstream os;
  LogDispatcher &logger;
};
}  // namespace acc

#endif  // _GTK_ACCOUNTING_LOG_H_
