#ifndef COURSEUI_H
#define COURSEUI_H

#include <QWidget>
#include <../DTO/Course.h>

namespace Ui {
class CourseUI;
}

class CourseUI : public QWidget
{
    Q_OBJECT

public:
    explicit CourseUI(Course course, QWidget *parent = nullptr);
    ~CourseUI();

private slots:
    void on_pushButton_clicked();

    void on_registerBtn_clicked();

private:
    void initialize();

private:
    Ui::CourseUI *ui;
    Course course;
};

#endif // COURSEUI_H
