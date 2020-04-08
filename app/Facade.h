#ifndef _GTK_ACCOUNTING_APP_FACADE_H_
#define _GTK_ACCOUNTING_APP_FACADE_H_

#include "Builder.h"

class Facade
{
    public:
    Facade();

    Builder& builder();

    private:
    Builder m_builder;
};

#endif // _GTK_ACCOUNTING_APP_FACADE_H_
