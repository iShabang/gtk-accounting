#ifndef _GTK_ACCOUNTING_APP_FACADE_H_
#define _GTK_ACCOUNTING_APP_FACADE_H_

#include "Builder.h"
#include "Table.h"

#include <gtk-accounting/LibFacadeInterface.h>

class Facade
{
    public:
    Facade(acc::LibFacadeInterface &lib);

    Builder &builder();


    private:
    Builder m_builder;
    Table m_table;
};

#endif // _GTK_ACCOUNTING_APP_FACADE_H_
