#ifndef _GTK_ACCOUNTING_SCOPED_CONNECTION_H_
#define _GTK_ACCOUNTING_SCOPED_CONNECTION_H_

#include <sigc++/connection.h>

namespace acc {

class ScopedConnection :  public sigc::connection {

  public:
    ScopedConnection();
    ScopedConnection(sigc::slot_base& slot);
    ScopedConnection(const ScopedConnection &);
    ScopedConnection(const sigc::connection &);
    ~ScopedConnection();
};

};

#endif // _GTK_ACCOUNTING_SCOPED_CONNECTION_H_
