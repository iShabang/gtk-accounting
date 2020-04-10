#include <gtk-accounting/MainDispatcher.h>

namespace acc {

void MainDispatcher::queueEvent(DispatchEvent event) {
  m_dispatchThread.queueEvent(event);
}

void MainDispatcher::DispatchThread::queueEvent(DispatchEvent) {
  m_mutex.lock();
}

}
