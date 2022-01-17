#ifndef TESTADVERTISEWIDGET_H
#define TESTADVERTISEWIDGET_H

#include <QWidget>
#include <../DTO/Test.h>
#include <../DTO/Course.h>

namespace Ui {
    class TestAdvertiseWidget;
}

class TestAdvertiseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestAdvertiseWidget(Course course, int testIdx, QWidget *parent = nullptr);
    ~TestAdvertiseWidget();

public:
    void initialize();

private:
    Ui::TestAdvertiseWidget *ui;
    Test* test;
    Course course;
    int testIndex;
};

#endif // TESTADVERTISEWIDGET_H
