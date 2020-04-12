#include "Table.h"

#include <gtkmm/checkbutton.h>
#include <gtkmm/label.h>
#include <string>

Table::Table(acc::TransactionInterface &tran, Builder& builder) : m_tran(tran), m_builder(builder), m_tranConn(tran.transactionsReceived().connect([this](std::vector<acc::Transaction> data){ onTransactions(data); })) {
  m_builder.getWidget("tableBox",m_tableBox);
  m_tran.requestTransactions();
}

void Table::onTransactions(std::vector<acc::Transaction> data) {
  for (auto &&i : data) {
    // create a horizontal box
    Gtk::Box box;
    box.set_halign(Gtk::ALIGN_FILL);
    // add checkbox widget
    Gtk::CheckButton checkButton;
    checkButton.set_label("");
    box.add(checkButton);

    // add name label
    Gtk::Label nameLabel;
    nameLabel.set_label(i.name);
    box.add(nameLabel);
    // add date label
    Gtk::Label dateLabel;
    nameLabel.set_label(i.date);
    box.add(dateLabel);

    // add amount label
    Gtk::Label amountLabel;
    nameLabel.set_label(std::to_string(i.amount));
    box.add(amountLabel);

    m_tableBox->add(box);
  }
}
