#include "InfoBox.h"

#include <gtk-accounting/Precision.h>
#include <gtkmm/label.h>
#include <string>

InfoBox::InfoBox(Builder &builder, acc::TransactionInterface &tran)
    : m_builder(builder),
      m_tran(tran),
      m_totalConn(tran.currentTotal().connect([this](const double &total) { onTotalAmount(total); })),
      m_log("InfoBox")
{
}

void InfoBox::onTotalAmount(const double &total) {
  Gtk::Label *label = nullptr;
  m_builder.getWidget("totalLabel",label);

  if (!label)
  {
    LOG(acc::ERROR,m_log) << "onTotalAmount(): Label not found"; 
    return;
  }

  label->set_label(acc::doubleToString(total));
}
