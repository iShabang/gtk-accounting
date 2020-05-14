#ifndef _GTK_ACCOUNTING_MAIN_DISPATCHER_H_
#define _GTK_ACCOUNTING_MAIN_DISPATCHER_H_

#include <gtk-accounting/dispatch/DispatchInterface.h>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace acc {

class MainDispatcher : public DispatchInterface {
 public:
  MainDispatcher();

  ~MainDispatcher();
  MainDispatcher(const MainDispatcher &) = delete;
  MainDispatcher(MainDispatcher &&) = delete;
  MainDispatcher &operator=(const MainDispatcher &) = delete;
  MainDispatcher &operator=(MainDispatcher &&) = delete;

 private:
  void queueEvent(DispatchEvent);
  void shutdown();

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
    void shutdown();
    void threadFunction();

   private:
    std::queue<DispatchEvent> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_running;
  };

  DispatchThread m_dispatchThread;
  std::thread m_thread;
};

}  // namespace acc

#endif  // _GTK_ACCOUNTING_MAIN_DISPATCHER_H_
