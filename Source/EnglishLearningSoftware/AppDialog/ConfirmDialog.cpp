#include "ConfirmDialog.h"

#include <QLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <Constant/ConstantGUI.h>

ConfirmDialog::ConfirmDialog(QString message)
{
    QWidget* buttonBoxWidget = new QWidget(this);
    buttonBoxWidget->setLayout(new QHBoxLayout);

    QPushButton* acceptButton = new QPushButton("Ok");
    QPushButton* cancelButton = new QPushButton("Cancel");

    this->setFixedWidth(400);

    acceptButton->setStyleSheet(ConstantGUI::CONFIRM_DIALOG_BUTTON_ACCEPTED);
    cancelButton->setStyleSheet(ConstantGUI::CONFIRM_DIALOG_BUTTON_REJECTED);

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    acceptButton->setFixedSize(130, 40);
    cancelButton->setFixedSize(130, 40);

    buttonBoxWidget->layout()->addWidget(acceptButton);
    buttonBoxWidget->layout()->addWidget(cancelButton);

    QLabel* message_label = new QLabel(message, this);
    message_label->setFixedHeight(100);
    message_label->setWordWrap(true);
    message_label->setStyleSheet(ConstantGUI::DIALOG_MESSAGE_STYLE);
    message_label->setAlignment(Qt::AlignHCenter);

    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(message_label);
    this->layout()->addWidget(buttonBoxWidget);

    this->layout()->setAlignment(Qt::AlignJustify);
}

ConfirmDialog::~ConfirmDialog()
{
    // do nothing, hehe
}
