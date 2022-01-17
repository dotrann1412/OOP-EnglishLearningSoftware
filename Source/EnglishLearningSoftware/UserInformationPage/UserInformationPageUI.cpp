#include "UserInformationPageUI.h"
#include "ui_UserInformationPageUI.h"

#include <AppDialog/ChangePasswordUI.h>
#include <../BUS/Session.h>
#include <Constant/ConstantGUI.h>
#include <../BUS/UserManagement.h>

#include <AppDialog/ConfirmDialog.h>
#include <AppDialog/MessageDialog.h>
#include <AppDialog/ReportFormUI.h>

UserInformationPageUI::UserInformationPageUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInformationPageUI)
{
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
        ChangePasswordUI* widget = new ChangePasswordUI(nullptr);
        widget->show();
    }
    else {
        ReportFormUI* form = new ReportFormUI();
        form->show();
    }
}

void UserInformationPageUI::initializeUserInformation() {
    User* user = Session::getInstance()->getUserAttempt();

    if(!user)  {
        // maybe show dialog here
        return;
    }

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
    User* user = Session::getInstance()->getUserAttempt();

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

        QDialog* dialog = new ConfirmDialog("Change your personal information?");

        int dialog_result = dialog->exec();

        isEditting = false;
        if(dialog_result == QDialog::Rejected) {
            this->initializeUserInformation();
            return;
        }

        string date = ui->dayOfBirth->text().toStdString();

        QString log = "";
        if(Date::validate(date))
           user->setDayOfBirth(date);
        else
            log += "Invalid date\n";

        user->setName(ui->name->text().toStdString());
        user->setEmail(ui->email->text().toStdString()); // validation?
        user->setPhoneNumber(ui->phoneNumber->text().toStdString()); // validation?
        UserManagement::saveChange(user);

        ui->error_log->setText(log);
        this->initializeUserInformation();

        QDialog* message_dialog = new MessageDialog("Your information has been saved");
        message_dialog->exec();
    }
}

