#include "Facade.h"

Facade::Facade() : m_builder("../glade/main-window.glade") {}

Builder &Facade::builder() { return m_builder; }
