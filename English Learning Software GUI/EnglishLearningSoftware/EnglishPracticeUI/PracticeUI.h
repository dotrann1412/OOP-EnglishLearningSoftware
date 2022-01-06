#ifndef PRACTICEUI_H
#define PRACTICEUI_H

#include <QFrame>
#include <QPushButton>

namespace Ui {
class EnglishTest;
}

class EnglishTest : public QFrame
{
    Q_OBJECT

public:
    explicit EnglishTest(QWidget *parent = nullptr);
    EnglishTest(int count = 0);
    ~EnglishTest();

private:
    Ui::EnglishTest *ui;
    QPushButton* question;
    int count;

private:

    void initialized();
};

#endif // PRACTICEUI_H
