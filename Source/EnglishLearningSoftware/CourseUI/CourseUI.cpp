#include "CourseUI.h"
#include "ui_CourseUI.h"

#include <Constant/ConstantGUI.h>
#include <VScrollArea/VerticalScrollArea.h>
#include <QLayout>
#include <TestAdvertiseWidget/TestAdvertiseWidget.h>
#include <../BUS/Helper.h>

#include <AppDialog/MessageDialog.h>
#include <../BUS/Session.h>

CourseUI::CourseUI(Course course, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseUI)
{
    this->setFixedSize(1302, 752);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->course = course;

    CoursesManagement::resizeCurrenScore(course.numOfTest());


    ui->setupUi(this);
    this->initialize();
}

CourseUI::~CourseUI()
{
    vector<int > Score = CoursesManagement::getCurrenScore();
    for(auto res: Score)
        std::cerr << res << ' ';
    std::cerr << '\n';
    std::cerr << "progess saved!\n";
    CoursesManagement::SaveProgress(Session::getInstance()->getUserAttempt(),&this->course,Score);
    delete ui;
}

void CourseUI::initialize() {
    VerticalScrollArea* scrollarea = new VerticalScrollArea(1, ui->testList);

    User* user = Session::getInstance()->getUserAttempt();
    if(user) {
        if(user->isRegistered(course.getName())) {
            ui->registerBtn->setText("Unregister");
        } else {
            ui->registerBtn->setText("Register");
        }
    }

    ui->testList->setLayout(new QVBoxLayout);

    for(int i = 0, n = course.numOfTest(); i < n; ++i) {
        scrollarea->addWidget(new TestAdvertiseWidget(course, i, this));
    }

    ui->testList->layout()->setAlignment(scrollarea, Qt::AlignCenter);
    ui->testList->layout()->addWidget(scrollarea);

    if(course.numOfTest() == 0) {
        QLabel* label = new QLabel(this);
        label->setText("This course doesn't have any test!");
        ui->testList->layout()->addWidget(label);
    }

    ui->registerBtn->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
    ui->authorLbl->setText(QString::fromStdString(course.getModifier()));
    ui->dayModifyLbl->setText(QString::fromStdString(course.getDayModify().toString()));
    ui->courseName->setText(QString::fromStdString(Helper::toUpper(course.getName())));
    ui->ratingLbl->setText(QString::fromStdString(std::to_string(course.getDifficulty())));
    ui->descriptionTxtBox->setText(QString::fromStdString(course.getIntro()));
    ui->descriptionTxtBox->setEnabled(false);
}

void CourseUI::on_pushButton_clicked()
{
    this->close();
}

void CourseUI::on_registerBtn_clicked()
{
    Session* session = Session::getInstance();
    if(!session->getUserAttempt())
    {
        ui->registerBtn->setText("Register");
        QDialog* dialog = new MessageDialog("Forbiden!");
        dialog->exec();
    } else {
        bool result = Session::getInstance()->addUserCourse(this->course);
        QString message = "";
        if(result) {
            message = "Course added successfuly!";
        } else message = "The course has already in your course list!";
        QDialog* dialog = new MessageDialog(message);
        dialog->exec();
        ui->registerBtn->setText("Unregister");
    }
}
