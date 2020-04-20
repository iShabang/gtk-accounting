#ifndef _GTK_ACCOUNTING_LOG_CHANNEL_H_
#define _GTK_ACCOUNTING_LOG_CHANNEL_H_

#include <gtk-accounting/Log.h>

#include <string>

namespace acc {

#define LOG(level, channel)         \
  if (level < acc::Log::getLevel()) \
    ;                               \
  else                              \
    acc::Log().getStream(level, channel.name())

class LogChannel {
 public:
  LogChannel(const std::string &name);
  std::string name();

 private:
  std::string m_channelName;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_LOG_CHANNEL_H_
