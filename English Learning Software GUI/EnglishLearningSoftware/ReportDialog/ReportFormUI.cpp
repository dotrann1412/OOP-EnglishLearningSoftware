#include "ReportFormUI.h"
#include "ui_ReportFormUI.h"

ReportFormUI::ReportFormUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportFormUI)
{
    ui->setupUi(this);
}

ReportFormUI::~ReportFormUI()
{
    delete ui;
}
