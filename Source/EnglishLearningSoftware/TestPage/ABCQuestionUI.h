#ifndef ABCQUESTIONUI_H
#define ABCQUESTIONUI_H

#include <QWidget>
#include <string>
#include <../DTO/Question.h>
#include <../DTO/ABCQuestion.h>
#include <QPushButton>
#include <vector>

class ABCQuestionUI : public QWidget
{
    Q_OBJECT
public:
    explicit ABCQuestionUI(ABCQuestion* question, QWidget *parent = nullptr);
    ~ABCQuestionUI();
private:
    void initialize();

public:
    std::vector<std::string> getUserAns();
    bool validate(std::vector<std::string> result);
    void setEditAble(bool flag);

private:
    ABCQuestion* question;

    vector<vector<QPushButton*>> ansButton;
    std::vector<int> ansChoosed;
};

#endif // ABCQUESTIONUI_H
