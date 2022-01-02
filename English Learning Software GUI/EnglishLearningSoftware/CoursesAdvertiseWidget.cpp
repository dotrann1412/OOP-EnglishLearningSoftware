#include "CoursesAdvertiseWidget.h"
#include "ui_coursesadvertise.h"

#include "ConstantGUI.h"

#include "PracticeUI.h"

CoursesAdvertise::CoursesAdvertise(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoursesAdvertise)
{
    ui->setupUi(this);
    QPixmap pixmap(":/resources/courses/default.jpg");
    pixmap = pixmap.scaled(ui->demoLbl->size(),Qt::KeepAspectRatio);
    ui->demoLbl->setPixmap(pixmap);

    ui->coursesName->setText("Demo");
    ui->authorLbl->setText("DoTran");
    ui->dayModifiedLbl->setText("10/12/2021");
    ui->questionNumberLbl->setText("nan");

    ui->coursesName->setStyleSheet(ConstantGUI::LINE_PUSH_BUTTON_HOVER_STYLE);
}

CoursesAdvertise::CoursesAdvertise(QWidget *parent, int courses) :
    QWidget(parent),
    ui(new Ui::CoursesAdvertise)
{
    ui->setupUi(this);
    QPixmap pixmap(":/resources/courses/default.jpg");
    pixmap = pixmap.scaled(ui->demoLbl->size(),Qt::KeepAspectRatio);
    ui->demoLbl->setPixmap(pixmap);

    ui->coursesName->setText("Demo");
    ui->authorLbl->setText("DoTran");
    ui->dayModifiedLbl->setText("10/12/2021");
    ui->questionNumberLbl->setText("nan");

    ui->coursesName->setStyleSheet(ConstantGUI::LINE_PUSH_BUTTON_HOVER_STYLE);
}

CoursesAdvertise::~CoursesAdvertise()
{
    delete ui;
}

void CoursesAdvertise::on_coursesName_clicked()
{
    EnglishTest* test = new EnglishTest(nullptr);
    test->show();
}

