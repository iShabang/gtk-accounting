#include "Table.h"

#include <gtk-accounting/Precision.h>
#include <gtk-accounting/Time.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

#include <iostream>
#include <string>

Table::Table(acc::TransactionInterface &tran, Builder &builder)
    : m_tran(tran),
      m_builder(builder),
      m_tranConn(tran.transactionsReceived().connect(
          [this](std::vector<acc::Transaction> data) { onTransactions(data); })),
      m_align(0.1) {
  m_builder.getWidget("tableBox", m_tableBox);
  setHeaderAlignment(m_align);
  m_tran.requestTransactions();
}

void Table::onTransactions(std::vector<acc::Transaction> data) {
  std::cout << "onTransactions. length: " << data.size() << std::endl;
  for (auto &&i : data) {
    Gtk::Box *box = createTableEntry(i);
    m_tableBox->pack_start(*box);
    m_tableBox->show_all_children();
  }
}

Gtk::Box *Table::createTableEntry(const acc::Transaction &transaction) {
  Gtk::Box *box = Gtk::make_managed<Gtk::Box>();
  Gtk::CheckButton *checkButton = Gtk::make_managed<Gtk::CheckButton>();
  Gtk::Label *nameLabel = Gtk::make_managed<Gtk::Label>(transaction.name, Gtk::ALIGN_FILL);
  Gtk::Label *dateLabel =
      Gtk::make_managed<Gtk::Label>(acc::formatDate(transaction.date), Gtk::ALIGN_FILL);
  Gtk::Label *amountLabel =
      Gtk::make_managed<Gtk::Label>(acc::floatToString(transaction.amount), Gtk::ALIGN_FILL);
  Gtk::Frame *checkFrame = Gtk::make_managed<Gtk::Frame>();
  Gtk::Frame *nameFrame = Gtk::make_managed<Gtk::Frame>();
  Gtk::Frame *dateFrame = Gtk::make_managed<Gtk::Frame>();
  Gtk::Frame *amountFrame = Gtk::make_managed<Gtk::Frame>();

  checkFrame->set_name("tableCell");
  nameFrame->set_name("tableCell");
  dateFrame->set_name("tableCell");
  amountFrame->set_name("tableCell");

  box->set_halign(Gtk::ALIGN_FILL);
  box->set_homogeneous(true);

  checkButton->set_label("");
  checkButton->set_halign(Gtk::ALIGN_FILL);
  checkFrame->add(*checkButton);
  uint64_t id = transaction.id;
  checkButton->signal_toggled().connect([this, checkButton, id]() { onSelected(checkButton, id); });
  box->pack_start(*checkFrame);

  gtk_label_set_xalign(nameLabel->gobj(), m_align);
  nameFrame->add(*nameLabel);
  box->pack_start(*nameFrame);

  gtk_label_set_xalign(dateLabel->gobj(), m_align);
  dateFrame->add(*dateLabel);
  box->pack_start(*dateFrame);

  gtk_label_set_xalign(amountLabel->gobj(), m_align);
  amountFrame->add(*amountLabel);
  box->pack_start(*amountFrame);

  return box;
}

void Table::setHeaderAlignment(const float &value) {
  Gtk::Label *label = nullptr;

  m_builder.getWidget("headerNameLabel", label);
  gtk_label_set_xalign(label->gobj(), value);

  m_builder.getWidget("headerDateLabel", label);
  gtk_label_set_xalign(label->gobj(), value);

  m_builder.getWidget("headerAmountLabel", label);
  gtk_label_set_xalign(label->gobj(), value);
}

void Table::onSelected(Gtk::CheckButton *checkBtn, const uint64_t &id) {
  if (checkBtn != nullptr) {
    bool select = false;
    if (checkBtn->get_active()) {
      select = true;
    }

    m_tran.selectTransaction(id, select);
  }
}
