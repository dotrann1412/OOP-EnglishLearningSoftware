#ifndef COURSESADVERTISEWIDGET_H
#define COURSESADVERTISEWIDGET_H

#include <QWidget>
#include <../BUS/CoursesManagement.h>
#include <CourseUI/CourseUI.h>
#include <../DTO/Course.h>

namespace Ui {
class CoursesAdvertise;
}

class CoursesAdvertise : public QWidget
{
    Q_OBJECT

public:
    CoursesAdvertise(Course courses, QWidget *parent = nullptr);
    ~CoursesAdvertise();

private slots:
    void on_coursesName_clicked();

private:
    Ui::CoursesAdvertise *ui;
    Course course;
    // just get the information about the course
    // like name, day modified, author, ..
};

#endif // COURSESADVERTISEWIDGET_H
