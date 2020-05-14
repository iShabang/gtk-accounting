#include <gtk-accounting/log/LogChannel.h>

#include <sstream>

namespace acc {

LogChannel::LogChannel(const std::string &name)
    : m_channelName(name) {}

std::string LogChannel::name() { return m_channelName; }

}  // namespace acc
