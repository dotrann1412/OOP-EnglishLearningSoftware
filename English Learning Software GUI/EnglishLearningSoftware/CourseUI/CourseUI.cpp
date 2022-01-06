#include "CourseUI.h"
#include "ui_CourseUI.h"

CourseUI::CourseUI(std::string coursePath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseUI)
{
    course.Load(coursePath);
    this->initialize();

    this->setFixedSize(1291, 614);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);
}

CourseUI::~CourseUI()
{
    delete ui;
}

void CourseUI::initialize() {
    this->ui->authorLbl->setText(QString::fromStdString(course.getModifier()));

    this->ui->dayModifyLbl->setText(QString::fromStdString(course.getDayModify().toString()));

    this->ui->courseName->setText(QString::fromStdString(course.getName()));
    this->ui->ratingLbl->setText(QString::fromStdString(std::to_string(course.getDifficulty())));

    this->ui->descriptionTxtBox->setText(QString::fromStdString(course.getIntro()));
    ui->descriptionTxtBox->setEnabled(false);
}

void CourseUI::on_pushButton_clicked()
{
    this->close();
}
