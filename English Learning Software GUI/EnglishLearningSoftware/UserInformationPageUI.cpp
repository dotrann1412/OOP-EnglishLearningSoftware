#include "UserInformationPageUI.h"
#include "ui_UserInformationPageUI.h"

#include "ChangePasswordUI.h"
#include "ConstantGUI.h"

UserInformationPageUI::UserInformationPageUI(User* user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInformationPageUI)
{
    this->user = user;
    this->isEditting = false;
    ui->setupUi(this);
    this->initializeUserInformation();
}

UserInformationPageUI::~UserInformationPageUI()
{
    delete ui;
}

void UserInformationPageUI::on_label_8_linkActivated(const QString &link)
{

    if(link == "change_password") {
        ChangePasswordUI* widget = new ChangePasswordUI(user, nullptr);
        widget->show();
    }
    else {

    }
}

void UserInformationPageUI::initializeUserInformation() {
    ui->username->setText(QString::fromStdString(user->getUserName()));
    ui->role->setText(user->getRole() == User::ADMIN ? "Admin"
                                                     : (user->getRole() == User::TEACHER ? "Teacher" : "Student"));
    ui->email->setText(QString::fromStdString(user->getEmail()));
    ui->dayOfBirth->setText(QString::fromStdString(user->getDayOfBirth().toString()));
    ui->name->setText(QString::fromStdString(user->getName()));
    ui->phoneNumber->setText(QString::fromStdString(user->getPhoneNumber()));

    ui->username->setReadOnly(true);
    ui->email->setReadOnly(true);
    ui->dayOfBirth->setReadOnly(true);
    ui->name->setReadOnly(true);
    ui->phoneNumber->setReadOnly(true);
    ui->role->setReadOnly(true);

    ui->username->setStyleSheet(ConstantGUI::LINE_EDIT_READ_ONLY);
    ui->email->setStyleSheet(ConstantGUI::LINE_EDIT_READ_ONLY);
    ui->dayOfBirth->setStyleSheet(ConstantGUI::LINE_EDIT_READ_ONLY);
    ui->name->setStyleSheet(ConstantGUI::LINE_EDIT_READ_ONLY);
    ui->phoneNumber->setStyleSheet(ConstantGUI::LINE_EDIT_READ_ONLY);
    ui->role->setStyleSheet(ConstantGUI::LINE_EDIT_READ_ONLY);

    ui->pushButton->setText("Edit");
}

void UserInformationPageUI::on_pushButton_clicked()
{
    if(!isEditting) {
        isEditting = true;
        ui->email->setReadOnly(false);
        ui->dayOfBirth->setReadOnly(false);
        ui->name->setReadOnly(false);
        ui->phoneNumber->setReadOnly(false);

        ui->email->setStyleSheet(ConstantGUI::LINE_EDIT_IS_EDITTING);
        ui->dayOfBirth->setStyleSheet(ConstantGUI::LINE_EDIT_IS_EDITTING);
        ui->name->setStyleSheet(ConstantGUI::LINE_EDIT_IS_EDITTING);
        ui->phoneNumber->setStyleSheet(ConstantGUI::LINE_EDIT_IS_EDITTING);

        ui->pushButton->setText("Save");
    } else {

        isEditting = false;
        string date = ui->dayOfBirth->text().toStdString();

        QString log = "";
        if(Date::validate(date))
           user->setDayOfBirth(date);
        else
            log += "Invalid date";

        this->user->setName(ui->name->text().toStdString());
        this->user->setEmail(ui->email->text().toStdString()); // validation?
        this->user->setPhoneNumber(ui->phoneNumber->text().toStdString()); // validation?
        this->user->save();

        ui->error_log->setText(log);
        this->initializeUserInformation();
    }
}

