#include "RankingRow.h"

#include <QLayout>
#include <QLabel>
#include <QPushButton>

#include <Constant/ConstantGUI.h>
#include <iostream>

using std::vector;
using std::string;

RankingRow::RankingRow(std::string num, std::vector<std::string> row, QWidget *parent)
    : QWidget{parent}
{
    if(num == "") {
        this->setStyleSheet(ConstantGUI::QUESTION_STATEMENT_STYLE_2);
    }

    setLayout(new QHBoxLayout);
    layout()->setAlignment(Qt::AlignJustify);
    setFixedHeight(40);

    QLabel** label = new QLabel*[row.size()];
    QLabel* idx_label = new QLabel(QString::fromStdString(num), this);
    layout()->addWidget(idx_label);

    for(int i = 0; i < row.size(); ++i) {
        if(i || num == "") {
            label[i] = new QLabel(QString::fromStdString(row[i]), this);
            label[i]->setAlignment(Qt::AlignCenter);
            label[i]->setFixedWidth(200);
            this->layout()->addWidget(label[i]);
        } else {
            QPushButton* button = new QPushButton(QString::fromStdString(row[i]) ,this);
            button->setFixedWidth(250);
            button->setStyleSheet(ConstantGUI::LINE_PUSH_BUTTON_HOVER_STYLE);

            connect(button, &QPushButton::clicked, [this] {
                std::cerr << "clicked" << '\n';
            });

            layout()->addWidget(button);
        }
    }

    delete label;
}
