#include "AddCourseUI.h"
#include "ui_AddCourseUI.h"

#include <QFileDialog>
#include <VScrollArea/VerticalScrollArea.h>
#include <TestAdvertiseWidget/TestAdvertiseWidget.h>
#include <AppDialog/ConfirmDialog.h>

AddCourseUI::AddCourseUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCourseUI)
{
    this->setFixedSize(900, 615);
    this->testPane = new VerticalScrollArea(1, this);
    this->course = new Course();
    ui->setupUi(this);
}

AddCourseUI::~AddCourseUI()
{
    // add course here
    delete ui;
}

void AddCourseUI::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    this->ntestpath.push_back(fileName.toStdString());
    QWidget* widget = new TestAdvertiseWidget(*course, ntestpath.size(), this);
    widget->setEnabled(false);
    ((VerticalScrollArea*)this->testPane)->addWidget(widget);
}

void AddCourseUI::on_name_editingFinished()
{
    course->setName(ui->name->text().toStdString());
}

void AddCourseUI::on_intro_textChanged()
{
    course->setIntro(ui->intro->toPlainText().toStdString());
}

void AddCourseUI::on_name_2_editingFinished()
{
    course->setDifficulty(ui->diff->text().toInt());
}


void AddCourseUI::on_pushButton_2_clicked()
{
    QDialog* dialog = new ConfirmDialog("Add " + QString::fromStdString(course->getName()));
    int dialog_result = dialog->exec();
    if(dialog_result == QDialog::Accepted) {
        this->AddCourse(this->ntestpath,*this->course);
        this->close();
    }
}

void AddCourseUI::AddCourse(vector<string> testPath,Course course)
{
    course.clearTest();
    for(auto t:testPath)
        course.addTest(t);
    User* user = Session::getInstance()->getUserAttempt();
    course.setModify(user->getName(),Date::now());
    CourseInfo info;
    info.Modifier = course.getModifier();
    info.difficulty = course.getDifficulty();
    info.name =  course.getName();
    info.path = course.Write();
    CoursesManagement::AddCourse(info);
    CoursesManagement::SaveData();
}
