#ifndef ADMINTASKPAGEUI_H
#define ADMINTASKPAGEUI_H

#include <QWidget>

#include <../DTO/Admin.h>
#include <../DTO/Task.h>

namespace Ui {
class AdminTaskPageUI;
}

class AdminTaskPageUI : public QWidget
{
    Q_OBJECT

public:
    explicit AdminTaskPageUI(QWidget *parent = nullptr);
    ~AdminTaskPageUI();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AdminTaskPageUI *ui;

    Admin* admin;
    bool isDoing;
};

#endif // ADMINTASKPAGEUI_H
