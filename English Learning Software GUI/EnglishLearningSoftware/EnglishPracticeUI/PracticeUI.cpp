#include "PracticeUI.h"
#include "ui_PracticeUI.h"

#include <string>
#include <QScrollBar>
#include <QFrame>

#include <VScrollArea/VerticalScrollArea.h>
#include <Constant/ConstantGUI.h>

EnglishTest::EnglishTest(QWidget *parent)
    : QFrame(parent),
    ui(new Ui::EnglishTest)
{
    this->setFixedWidth(1291);
    this->setFixedHeight(763);

    ui->setupUi(this);
    this->ui->frame->setLayout(new QVBoxLayout);
    this->ui->frame->setFixedWidth(this->ui->frame->width());

    VerticalScrollArea* scrollarea = new VerticalScrollArea(3);
    scrollarea->setFixedWidth(this->ui->frame->width());

    const float scaleRate = 0.8;

    for(int i = 0; i < 100; ++i) {
        QPushButton* pushButton = new QPushButton(QString::fromStdString(std::to_string(i)));

        pushButton->setFixedWidth(ConstantGUI::QUESTION_BUTTON_WIDTH * scaleRate);
        pushButton->setFixedHeight(ConstantGUI::QUESTION_BUTTON_HEIGHT * scaleRate);
        pushButton->setStyleSheet(ConstantGUI::PUSH_BUTTON_WITH_HOVER_STYLE);

        scrollarea->addWidget(pushButton);
        pushButton->setVisible(true);
    }

    this->ui->frame->layout()->addWidget(scrollarea);
}

EnglishTest::~EnglishTest()
{
    delete ui;
}

EnglishTest::EnglishTest(int count)
: ui(new Ui::EnglishTest)
{
    this->setFixedWidth(1291);
    this->setFixedHeight(763);

    ui->setupUi(this);
    this->ui->frame->setLayout(new QVBoxLayout);
    this->ui->frame->setFixedWidth(400);

    VerticalScrollArea* scrollarea = new VerticalScrollArea(3);
    scrollarea->setFixedWidth(400);

    const float scaleRate = 0.8;

    for(int i = 0; i < 30; ++i) {
        QPushButton* pushButton = new QPushButton(QString::fromStdString(std::to_string(i)));

        pushButton->setFixedWidth(ConstantGUI::QUESTION_BUTTON_WIDTH * scaleRate);
        pushButton->setFixedHeight(ConstantGUI::QUESTION_BUTTON_HEIGHT * scaleRate);
        pushButton->setStyleSheet(ConstantGUI::PUSH_BUTTON_WITH_HOVER_STYLE);

        scrollarea->addWidget(pushButton);
        pushButton->setVisible(true);
    }

    this->ui->frame->layout()->addWidget(scrollarea);
}

void EnglishTest::initialized() {
}
