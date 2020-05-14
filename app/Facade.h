#ifndef _GTK_ACCOUNTING_APP_FACADE_H_
#define _GTK_ACCOUNTING_APP_FACADE_H_

#include <gtk-accounting/facade/LibFacadeInterface.h>

#include "AddTransactionPopup.h"
#include "Builder.h"
#include "InfoBox.h"
#include "MenuBox.h"
#include "Table.h"
#include "FilterWindow.h"

class Facade
{
 public:
  Facade(acc::LibFacadeInterface &lib);

  Builder &builder();

 private:
  Builder m_builder;
  Table m_table;
  AddTransactionPopup m_addTranPopup;
  FilterWindow m_filterWindow;
  MenuBox m_menuBox;
  InfoBox m_infoBox;
};

#endif  // _GTK_ACCOUNTING_APP_FACADE_H_
