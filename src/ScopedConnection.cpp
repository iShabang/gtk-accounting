#include <gtk-accounting/ScopedConnection.h>

namespace acc {

ScopedConnection::ScopedConnection() : connection() {}
ScopedConnection::ScopedConnection(sigc::slot_base& slot) : connection(slot) {}
ScopedConnection::ScopedConnection(const ScopedConnection& con) : connection(con) {}
ScopedConnection::~ScopedConnection() { disconnect(); }
ScopedConnection::ScopedConnection(const sigc::connection &conn) : connection(conn) {}

}  // namespace acc
