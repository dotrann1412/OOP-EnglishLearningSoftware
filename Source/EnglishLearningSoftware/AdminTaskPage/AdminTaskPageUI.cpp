#include "AdminTaskPageUI.h"
#include "ui_AdminTaskPageUI.h"

#include <../DTO/Admin.h>
#include <../DTO/Task.h>
#include <../BUS/Session.h>
#include <../BUS/TaskManagement.h>
#include <AppDialog/MessageDialog.h>
#include <QDialog>

AdminTaskPageUI::AdminTaskPageUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminTaskPageUI)
{
    ui->setupUi(this);
    admin = (Admin*)Session::getInstance()->getUserAttempt();
    Task task = admin->pendingTask();
    if(task.getTaskId() != "###") {
        ui->taskid->setText(QString::fromStdString(task.getTaskId()));
        ui->priority->setText(QString::number(task.getPriority()));
        ui->daymodify->setText(QString::fromStdString(task.getDayModify().toString()));
        ui->message->setText(QString::fromStdString(task.getMessage()));
        isDoing = true;
    } else {
        ui->taskid->setText("Nothing to do, hehe");
        ui->priority->clear();
        ui->daymodify->clear();
        ui->message->clear();
        isDoing = false;
    }
}

AdminTaskPageUI::~AdminTaskPageUI()
{
    delete ui;
}

void AdminTaskPageUI::on_pushButton_clicked()
{
    if(admin->markAsDone()) {
        QDialog* dialog = new MessageDialog("Task completed: " + ui->taskid->text());
        dialog->exec();
    } else return;

    Task task = admin->pendingTask();

    if(task.getTaskId() ==  "###") {
        ui->taskid->setText("Nothing to do, hehe");
        ui->priority->clear();
        ui->daymodify->clear();
        ui->message->clear();
        isDoing = false;
    } else {
        ui->taskid->setText(QString::fromStdString(task.getTaskId()));
        ui->priority->setText(QString::number(task.getPriority()));
        ui->daymodify->setText(QString::fromStdString(task.getDayModify().toString()));
        ui->message->setText(QString::fromStdString(task.getMessage()));
        isDoing = true;
    }
}

