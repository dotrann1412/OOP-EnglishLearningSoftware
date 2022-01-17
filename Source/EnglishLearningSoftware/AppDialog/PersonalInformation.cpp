#include "PersonalInformation.h"
#include "ui_PersonalInformation.h"

PersonalInformation::PersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalInformation)
{
    ui->setupUi(this);
}

PersonalInformation::~PersonalInformation()
{
    delete ui;
}
