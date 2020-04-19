#include <gtk-accounting/LogChannel.h>

#include <sstream>

namespace acc {

LogChannel::LogChannel(const std::string &name)
    : logger(LogDispatcher::getInstance()), m_channelName(name) {}

void LogChannel::debug(const std::string &message) {

  std::stringstream ss;
  ss << "DEBUG [" << m_channelName << "]: " << message;
  logger.queueMessage(ss.str());
}

void LogChannel::warning(const std::string &message) {
  std::stringstream ss;
  ss << "WARNING [" << m_channelName << "]: " << message;
  logger.queueMessage(message);
}

void LogChannel::error(const std::string &message) {
  std::stringstream ss;
  ss << "ERROR [" << m_channelName << "]: " << message;
  logger.queueMessage(message);
}

void LogChannel::critical(const std::string &message) {
  std::stringstream ss;
  ss << "CRITICAL [" << m_channelName << "]: " << message;
  logger.queueMessage(message);
}

}  // namespace acc
