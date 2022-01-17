#ifndef TFQUESTIONUI_H
#define TFQUESTIONUI_H

#include <QWidget>
#include <../DTO/TFQuestion.h>
#include <vector>
#include <string>
#include <QPushButton>

class TFQuestionUI : public QWidget
{
    Q_OBJECT
public:
    explicit TFQuestionUI(TFQuestion* question,QWidget *parent = nullptr);
    ~TFQuestionUI();
private:
    void initialize();

public:
    std::vector<std::string> getUserAns();
    bool validate(std::vector<std::string> result);
    void setEditAble(bool);

signals:

private:
    const static std::vector<std::pair<std::string, std::string>> _SIGNAL;

private:
    std::vector<int> ansChoosed;
    std::vector<std::vector<QPushButton*>> ansButton;
    TFQuestion* question;
};

#endif // TFQUESTIONUI_H
