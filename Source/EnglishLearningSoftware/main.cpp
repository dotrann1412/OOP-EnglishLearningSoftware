#include "HomeUI/HomeUI.h"

#include <QApplication>

vector<int> CoursesManagement::curScore;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Home w;
    w.show();
    return a.exec();
}
