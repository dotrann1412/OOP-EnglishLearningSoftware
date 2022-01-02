#ifndef CHANGEPASSWORDUI_H
#define CHANGEPASSWORDUI_H

#include <QWidget>
#include "../DTO/User.h"

namespace Ui {
class ChangePasswordUI;
}

class ChangePasswordUI : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswordUI(User* user, QWidget *parent = nullptr);
    ~ChangePasswordUI();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::ChangePasswordUI *ui;

private:
    User* user;
};

#endif // CHANGEPASSWORDUI_H
