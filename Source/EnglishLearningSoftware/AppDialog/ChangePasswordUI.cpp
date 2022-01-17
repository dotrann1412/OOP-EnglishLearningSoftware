#include "ChangePasswordUI.h"
#include "ui_ChangePasswordUI.h"

#include <QWidget>
#include <string>

#include <../BUS/Session.h>

using std::string;

ChangePasswordUI::ChangePasswordUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswordUI)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));

    this->setFixedWidth(522);
    this->setFixedHeight(264);

    this->setWindowModality(Qt::ApplicationModal);

    ui->setupUi(this);
}

ChangePasswordUI::~ChangePasswordUI()
{
    delete ui;
}

void ChangePasswordUI::on_checkBox_stateChanged(int arg1)
{
   if(arg1) {
       ui->newPassword->setEchoMode(QLineEdit::Normal);
   } else ui->newPassword->setEchoMode(QLineEdit::Password);
}


void ChangePasswordUI::on_pushButton_clicked()
{
    ui->error_log->clear();

    string currentPassword = ui->currentPassword->text().toStdString();
    string newPassword = ui->newPassword->text().toStdString();
    string reEntered = ui->re_enter->text().toStdString();

    for(auto x: newPassword) if(x == ' ' || x == '\t') {
        ui->error_log->setText("Password must not be contains white space");
        return;
    }

    if(newPassword != reEntered) {
        ui->error_log->setText("Password does not match");
        return;
    }

    User* user = Session::getInstance()->getUserAttempt();

    if(user && !user->changePassword(currentPassword, newPassword)) {
        ui->error_log->setText("Current password wrong");
        return;
    }

    this->close();
}

