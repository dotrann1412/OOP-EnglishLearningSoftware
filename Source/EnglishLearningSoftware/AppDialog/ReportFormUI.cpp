#include "ReportFormUI.h"
#include "ui_ReportFormUI.h"

#include <../BUS/TaskManagement.h>
#include <../BUS/Helper.h>
#include <../DTO/Task.h>
#include <AppDialog/MessageDialog.h>

ReportFormUI::ReportFormUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportFormUI)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(749, 389);
    ui->setupUi(this);
    ui->comboBox_2->addItems({"High", "Medium", "Low"});
    ui->comboBox->addItems({"Course", "User", "Another"});
}

ReportFormUI::~ReportFormUI()
{
    delete ui;
}

void ReportFormUI::on_pushButton_clicked()
{
    TaskManagement::report(Task(Helper::randomStr(10, "TSK"), (ui->comboBox_2->currentText() + "\n" + ui->message->toPlainText()).toStdString(), ui->comboBox->currentIndex()));
    MessageDialog* dialog = new MessageDialog("Report message sent!");
    dialog->exec();
    this->close();
}

