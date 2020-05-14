#ifndef _GTK_ACCOUNTING_MAIN_DISPATCHER_H_
#define _GTK_ACCOUNTING_MAIN_DISPATCHER_H_

#include <gtk-accounting/dispatch/DispatchInterface.h>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace acc {

/* Dispatch queue implementing the DispatchInterface. Utilizes a thread and a 
 * condition variable to listen for and run tasks in a single thread. This
 * keeps all library calls thread safe and sequential.
 */
class MainDispatcher : public DispatchInterface {
 public:
  MainDispatcher();

  ~MainDispatcher();
  MainDispatcher(const MainDispatcher &) = delete;
  MainDispatcher(MainDispatcher &&) = delete;
  MainDispatcher &operator=(const MainDispatcher &) = delete;
  MainDispatcher &operator=(MainDispatcher &&) = delete;

 private:
  // DispatchInterface methods
  void queueEvent(DispatchEvent);
  void shutdown();

 private:
  /* Internal thread object that actually runs the events. All library function calls
   * will basically live here. */
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

    /* Main function of the thread called by the OS */
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
