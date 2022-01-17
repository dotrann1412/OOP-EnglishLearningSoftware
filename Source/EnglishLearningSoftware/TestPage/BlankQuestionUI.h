#ifndef BLANKQUESTIONUI_H
#define BLANKQUESTIONUI_H

#include <QWidget>
#include <QLineEdit>

#include <../DTO/BlankQuestion.h>

class BlankQuestionUI : public QWidget
{
    Q_OBJECT
public:
    explicit BlankQuestionUI(BlankQuestion* question, QWidget *parent = nullptr);
    ~BlankQuestionUI();
public:
    std::vector<std::string> getUserAns();
    bool validate(std::vector<std::string> result);
    void setEditAble(bool flag);

private:
    void initialize();

signals:
private:
    BlankQuestion* question;
    std::vector<QLineEdit*> ansEditBox;
};

#endif // BLANKQUESTIONUI_H
