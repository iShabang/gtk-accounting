#ifndef _GTK_ACCOUNTING_MAIN_DISPATCHER_H_
#define _GTK_ACCOUNTING_MAIN_DISPATCHER_H_

#include <gtk-accounting/DispatchInterface.h>

#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace acc {

class MainDispatcher : public DispatchInterface {
 public:
  MainDispatcher();

  ~MainDispatcher() = default;
  MainDispatcher(const MainDispatcher &) = delete;
  MainDispatcher(MainDispatcher &&) = delete;
  MainDispatcher &operator=(const MainDispatcher &) = delete;
  MainDispatcher &operator=(MainDispatcher &&) = delete;

 private:
  void queueEvent(DispatchEvent);

 private:
  class DispatchThread {
   public:
    DispatchThread();

    ~DispatchThread() = default;
    DispatchThread(const DispatchThread &) = delete;
    DispatchThread(DispatchThread &&) = delete;
    DispatchThread &operator=(const DispatchThread &) = delete;
    DispatchThread &operator=(DispatchThread &&) = delete;

    void queueEvent(DispatchEvent);

    void threadFunction();

    // Listen for event

    // Dipatch event

    // If events in queue, dispatch again

    // If queue is empty, go back to listening

   private:
    std::queue<std::function<void()>> m_queue;
    std::mutex m_mutex;
  };

  DispatchThread m_dispatchThread;
  std::thread m_thread;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_MAIN_DISPATCHER_H_
