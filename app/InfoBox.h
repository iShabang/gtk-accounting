#ifndef _GTK_ACCOUNTING_APP_INFO_BOX_H_
#define _GTK_ACCOUNTING_APP_INFO_BOX_H_

#include "Builder.h"

#include <gtk-accounting/TransactionInterface.h>
#include <gtk-accounting/LogChannel.h>

class InfoBox
{
  public:
    InfoBox(Builder &builder, acc::TransactionInterface &tran);

    InfoBox(const InfoBox &) = delete;
    InfoBox(InfoBox &&) = delete;
    InfoBox& operator=(const InfoBox &) = delete;
    InfoBox& operator=(InfoBox &&) = delete;

  private:
    void onTotalAmount(const double &total);

  private:
    Builder &m_builder;

    acc::TransactionInterface &m_tran;
    acc::ScopedConnection m_totalConn;
    acc::LogChannel m_log;

};

#endif // _GTK_ACCOUNTING_APP_INFO_BOX_H_
