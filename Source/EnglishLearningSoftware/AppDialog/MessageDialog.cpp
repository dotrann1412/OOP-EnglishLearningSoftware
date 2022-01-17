#include "MessageDialog.h"

#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <Constant/ConstantGUI.h>

MessageDialog::MessageDialog(QString message)
{
    QPushButton* acceptButton = new QPushButton("Ok");
    acceptButton->setStyleSheet(ConstantGUI::CONFIRM_DIALOG_BUTTON_ACCEPTED);
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    acceptButton->setFixedSize(150, 40);
    this->setFixedWidth(400);
    QLabel* message_label = new QLabel(message, this);
    message_label->setFixedHeight(100);
    message_label->setWordWrap(true);
    message_label->setStyleSheet(ConstantGUI::DIALOG_MESSAGE_STYLE);
    message_label->setAlignment(Qt::AlignHCenter);

    this->setLayout(new QVBoxLayout);

    this->layout()->addWidget(message_label);
    this->layout()->addWidget(acceptButton);

    this->layout()->setAlignment(Qt::AlignJustify);
}
