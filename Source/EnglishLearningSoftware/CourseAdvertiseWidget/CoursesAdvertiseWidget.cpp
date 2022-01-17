#include "CoursesAdvertiseWidget.h"
#include "ui_CoursesAdvertiseWidget.h"

#include <Constant/ConstantGUI.h>
#include <EnglishPracticeUI/PracticeUI.h>
#include <../DTO/Date.h>

CoursesAdvertise::CoursesAdvertise(Course courses, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoursesAdvertise)
{
    this->course = courses;

    ui->setupUi(this);

    QPixmap pixmap(":/resources/courses/default.jpg");
    pixmap = pixmap.scaled(ui->demoLbl->size(),Qt::KeepAspectRatio);
    ui->demoLbl->setPixmap(pixmap);

    ui->coursesName->setText(QString::fromStdString(course.getName()));
    ui->authorLbl->setText(QString::fromStdString(course.getModifier()));

    // field missing
    ui->dayModifiedLbl->setText(QString::fromStdString(Date::now().toString()));
    ui->ratingLbl->setText(QString::fromStdString(to_string(course.getDifficulty())));

    ui->coursesName->setStyleSheet(ConstantGUI::LINE_PUSH_BUTTON_HOVER_STYLE);
}

CoursesAdvertise::~CoursesAdvertise()
{
    delete ui;
}

void CoursesAdvertise::on_coursesName_clicked()
{
    // open the course page for user regist
    CourseUI* fullCoursePage = new CourseUI(course, this->parentWidget()->parentWidget());
    fullCoursePage->show();
}
