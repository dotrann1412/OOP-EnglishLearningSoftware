#include "WelcomePage.h"
#include "ui_WelcomePage.h"

#include <QDesktopServices>

WelcomePage::WelcomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomePage)
{
    ui->setupUi(this);
}

WelcomePage::~WelcomePage()
{
    delete ui;
}

void WelcomePage::on_label_2_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link, QUrl::TolerantMode));
}
