#include "TeacherTaskPageUI.h"
#include "ui_TeacherTaskPageUI.h"

#include <UserInformationPage/AddCourseUI.h>
#include <../BUS/Session.h>
#include <../DTO/User.h>
#include <../DTO/Teacher.h>

#include <QLayout>
#include <VScrollArea/VerticalScrollArea.h>
#include <CourseAdvertiseWidget/CoursesAdvertiseWidget.h>

TeacherTaskPageUI::TeacherTaskPageUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherTaskPageUI)
{
    ui->setupUi(this);
    ui->frame->setLayout(new QVBoxLayout);

    Teacher* user = (Teacher*)Session::getInstance()->getUserAttempt();
    auto courseAddedList = user->getCoursesAddedList();
    ui->label_2->setText("You have added " + QString::number(courseAddedList.size()) + " course(s)!");

    VerticalScrollArea* scrollarea = new VerticalScrollArea(2, ui->frame);

    for(const auto& x: courseAddedList) {
        Course course;
        course.Load("../Data/Courses/" + x + "/course.txt");
        scrollarea->addWidget(new CoursesAdvertise(course, scrollarea));
    }

    ui->frame->layout()->addWidget(scrollarea);
}

TeacherTaskPageUI::~TeacherTaskPageUI()
{
    delete ui;
}

void TeacherTaskPageUI::on_pushButton_clicked()
{
    QWidget* widget = new AddCourseUI(nullptr);
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->show();
}

