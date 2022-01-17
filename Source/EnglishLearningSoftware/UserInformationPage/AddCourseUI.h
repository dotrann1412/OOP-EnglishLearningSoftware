#ifndef ADDCOURSEUI_H
#define ADDCOURSEUI_H

#include <QWidget>
#include <../DTO/Test.h>
#include <TestAdvertiseWidget/TestAdvertiseWidget.h>
#include <QWidget>
#include <../DTO/Course.h>
#include <../DTO/User.h>
#include <../BUS/Session.h>

namespace Ui {
class AddCourseUI;
}

class AddCourseUI : public QWidget
{
    Q_OBJECT

public:
    explicit AddCourseUI(QWidget *parent = nullptr);
    ~AddCourseUI();

private slots:
    void on_pushButton_clicked();

    void on_name_editingFinished();

    void on_intro_textChanged();

    void on_name_2_editingFinished();

    void on_pushButton_2_clicked();

    void AddCourse(vector<string> testPath,Course course);

private:
    Course* course;
    Ui::AddCourseUI *ui;
    QWidget* testPane;
    std::vector<std::string> ntestpath;
};

#endif // ADDCOURSEUI_H
