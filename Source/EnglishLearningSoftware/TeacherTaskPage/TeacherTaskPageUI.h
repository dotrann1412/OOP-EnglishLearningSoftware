#ifndef TEACHERTASKPAGEUI_H
#define TEACHERTASKPAGEUI_H

#include <QWidget>

namespace Ui {
class TeacherTaskPageUI;
}

class TeacherTaskPageUI : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherTaskPageUI(QWidget *parent = nullptr);
    ~TeacherTaskPageUI();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TeacherTaskPageUI *ui;
};

#endif // TEACHERTASKPAGEUI_H
