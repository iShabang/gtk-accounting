#include <gtk-accounting/MainDispatcher.h>
#include <iostream>
#include <unistd.h>

namespace acc {

MainDispatcher::MainDispatcher() : m_thread(&DispatchThread::threadFunction, &m_dispatchThread) {}

MainDispatcher::~MainDispatcher() {
  m_dispatchThread.shutdown();
  m_thread.join();
}

void MainDispatcher::queueEvent(DispatchEvent event) { m_dispatchThread.queueEvent(event); }

void MainDispatcher::shutdown() {
  m_dispatchThread.shutdown();
}

void MainDispatcher::DispatchThread::queueEvent(DispatchEvent event) {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_queue.push(event);
  lock.unlock();
  m_cv.notify_one();
}

void MainDispatcher::DispatchThread::shutdown() {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_running = false;
  lock.unlock();
  m_cv.notify_one();
}

void MainDispatcher::DispatchThread::threadFunction() {
  std::unique_lock<std::mutex> lock(m_mutex);
  do {
    m_cv.wait(lock, [this] { return (m_queue.size() || !m_running); });

    if (m_queue.size()) {
      DispatchEvent event = std::move(m_queue.front());

      lock.unlock();

      if (event) {
        event();
      }

      lock.lock();
    }
  } while (m_running);

}

MainDispatcher::DispatchThread::DispatchThread() : m_running(true) {}

}  // namespace acc
