#ifndef USERINFORMATIONPAGEUI_H
#define USERINFORMATIONPAGEUI_H

#include <QWidget>
#include "../DTO/User.h"

namespace Ui {
class UserInformationPageUI;
}

class UserInformationPageUI : public QWidget
{
    Q_OBJECT

public:
    explicit UserInformationPageUI(User* user, QWidget *parent = nullptr);
    ~UserInformationPageUI();

private slots:
    void on_label_8_linkActivated(const QString &link);

    void on_pushButton_clicked();

private:
    void initializeUserInformation();

private:
    Ui::UserInformationPageUI *ui;
    User* user;
    bool isEditting;
};

#endif // USERINFORMATIONPAGEUI_H
