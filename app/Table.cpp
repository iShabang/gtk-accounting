#include "Table.h"

#include <gtkmm/checkbutton.h>
#include <gtkmm/label.h>

#include <iostream>
#include <string>

Table::Table(acc::TransactionInterface &tran, Builder &builder)
    : m_tran(tran),
      m_builder(builder),
      m_tranConn(tran.transactionsReceived().connect(
          [this](std::vector<acc::Transaction> data) { onTransactions(data); })) {
  m_builder.getWidget("tableBox", m_tableBox);
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
  Gtk::Label *dateLabel = Gtk::make_managed<Gtk::Label>(transaction.date, Gtk::ALIGN_FILL);
  Gtk::Label *amountLabel =
      Gtk::make_managed<Gtk::Label>(std::to_string(transaction.amount), Gtk::ALIGN_FILL);

  box->set_halign(Gtk::ALIGN_FILL);
  box->set_homogeneous(true);

  checkButton->set_label("Select");
  checkButton->set_halign(Gtk::ALIGN_FILL);
  box->pack_start(*checkButton);

  gtk_label_set_xalign(nameLabel->gobj(), 0);
  box->pack_start(*nameLabel);

  gtk_label_set_xalign(dateLabel->gobj(), 0);
  box->pack_start(*dateLabel);

  gtk_label_set_xalign(amountLabel->gobj(), 0);
  box->pack_start(*amountLabel);

  return box;
}
