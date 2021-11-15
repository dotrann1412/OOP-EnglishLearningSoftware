#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
}

Home::~Home()
{
    delete ui;
}

