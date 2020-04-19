#ifndef _GTK_ACCOUNTING_LOG_CHANNEL_H_
#define _GTK_ACCOUNTING_LOG_CHANNEL_H_

#include <gtk-accounting/LogDispatcher.h>

#include <string>

namespace acc {

class LogChannel {

  public:
    LogChannel(const std::string &name);

    void debug(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
    void critical(const std::string &message);

  private:
    LogDispatcher &logger;
    std::string m_channelName;
};

}

#endif // _GTK_ACCOUNTING_LOG_CHANNEL_H_
