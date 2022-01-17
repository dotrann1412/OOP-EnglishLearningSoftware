#ifndef TESTPAGE_H
#define TESTPAGE_H

#include <QWidget>
#include <../DTO/Test.h>
#include <../DTO/Course.h>
#include <QPushButton>
#include <QTimer>

namespace Ui {
class TestPage;
}

class TestPage : public QWidget
{
    Q_OBJECT

public:
    explicit TestPage(Course course, int testIndex, QWidget *parent = nullptr);
    ~TestPage();

private:
    void initialize();

protected slots:
    void updateTimer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TestPage *ui;

protected slots:
    void showDetails();

private:
    Test* test;
    std::vector<QPushButton*> pushButton;
    std::vector<QWidget*> slide;
    int currentQuestion;
    vector<Question*> questions;
    vector<string> userAns;
    int testIndex;

    bool submitFlag;
};

#endif // TESTPAGE_H
