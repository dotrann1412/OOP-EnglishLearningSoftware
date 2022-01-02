#ifndef COURSESADVERTISEWIDGET_H
#define COURSESADVERTISEWIDGET_H

#include <QWidget>

namespace Ui {
class CoursesAdvertise;
}

class CoursesAdvertise : public QWidget
{
    Q_OBJECT

public:
    explicit CoursesAdvertise(QWidget *parent = nullptr, int courses = 0);
    CoursesAdvertise(QWidget *parent = nullptr);
    ~CoursesAdvertise();

private slots:
    void on_coursesName_clicked();

private:
    Ui::CoursesAdvertise *ui;
};

#endif // COURSESADVERTISEWIDGET_H
