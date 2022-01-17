#include "TestAdvertiseWidget.h"
#include "ui_TestAdvertiseWidget.h"

#include <QPixmap>
#include <Constant/ConstantGUI.h>
#include <QGraphicsDropShadowEffect>
#include <TestPage/TestPage.h>
#include <../BUS/Helper.h>
#include <AppDialog/MessageDialog.h>
#include <../DTO/User.h>
#include <../BUS/Session.h>

TestAdvertiseWidget::TestAdvertiseWidget(Course course,int testIndx, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestAdvertiseWidget)
{
    this->course = course;
    this->testIndex = testIndx;

    test = new Test();
    course.LoadTest(*test, testIndx);

    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    if(parent != nullptr) {
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
        effect->setOffset(0, 0);
        effect->setColor(QColor(68, 68, 68));
        effect->setBlurRadius(3);
        this->setGraphicsEffect(effect);
    }

    this->initialize();
}

void TestAdvertiseWidget::initialize() {
    QPixmap pixmap(":/resources/icon/play.png");
    pixmap = pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setPixmap(pixmap);

    ui->testId->setText(QString::fromStdString(Helper::toUpper(test->getName())));
    ui->progress->setText("0 / " + QString::fromStdString(std::to_string(test->questionCount())));

    ui->testId->setStyleSheet(ConstantGUI::LINE_PUSH_BUTTON_HOVER_STYLE);

    connect(ui->testId, &QPushButton::clicked, [this] {
        Session* session = Session::getInstance();
        QString message = "";

        if(!session) {
            message = "Session is not initialized";
        } else if(!session->getUserAttempt()) {
            message = "Login to enter this test";
        } else if(!session->getUserAttempt()->isRegistered(course.getName())) {
            message = "Register the course before enter this test";
        }

        if(message.size()) {
            QDialog* dialog = new MessageDialog(message);
            dialog->exec();
            return;
        }

        TestPage* testPage = new TestPage(course, this->testIndex,  nullptr);
        testPage->show();
    });
}

TestAdvertiseWidget::~TestAdvertiseWidget()
{
    delete test;
    delete ui;
}
