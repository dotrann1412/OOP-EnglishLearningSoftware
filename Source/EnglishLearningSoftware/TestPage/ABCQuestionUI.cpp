#include "ABCQuestionUI.h"

#include <QLabel>
#include <QLayout>
#include <VScrollArea/VerticalScrollArea.h>
#include <Constant/ConstantGUI.h>
#include <MediaPlayer/MediaPlayerWidget.h>

using std::string;

ABCQuestionUI::ABCQuestionUI(ABCQuestion* question, QWidget *parent)
    : QWidget(parent)
{
    this->setLayout(new QVBoxLayout);

    this->question = question;
    int subQuestionCount = question->getSubQuestionCount();
    ansButton.assign(subQuestionCount, vector<QPushButton*>(4, nullptr));
    this->ansChoosed.assign(subQuestionCount, -1);
    this->initialize();
}

ABCQuestionUI::~ABCQuestionUI() {

}

void ABCQuestionUI::initialize() {
    vector<string> subQuestion = question->getQuestionInfo();
    vector<string> selection[4];
    question->getSelection(selection);

    string _bigQuestion = question->getParagraph();
    QLabel* label = new QLabel(QString::fromStdString(_bigQuestion), this);
    label->setWordWrap(true);
    label->setStyleSheet(ConstantGUI::QUESTION_STATEMENT_STYLE_2);
    VerticalScrollArea* scrollarea = new VerticalScrollArea(1, this);
    scrollarea->setStyleSheet(ConstantGUI::VERTICAL_SCROLL_STYLE_S);
    scrollarea->addWidget(label);

    for(int i = 0, n = subQuestion.size(); i < n; ++i) {
        QLabel* statement = new QLabel(QString::fromStdString("Statement " + std::to_string(1 + i) + ": " +subQuestion[i]), this);
        statement->setWordWrap(true);
        statement->setStyleSheet(ConstantGUI::QUESTION_STATEMENT_STYLE_2);
        scrollarea->addWidget(statement);

        QWidget* gridWidget = new QWidget(this);
        gridWidget->setFixedHeight(130);
        QGridLayout* grid = new QGridLayout(gridWidget);

        for(int j = 0; j < 4; ++j) {
            ansButton[i][j] = new QPushButton(QString::fromStdString(selection[j][i]) ,this);
            ansButton[i][j]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
            ansButton[i][j]->setFixedHeight(50);
            connect(ansButton[i][j], &QPushButton::clicked, [this, i, j] {
                if(ansChoosed[i] != j) {
                    if(ansChoosed[i] >= 0) {
                        ansButton[i][ansChoosed[i]]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
                    }
                    ansButton[i][j]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
                    ansChoosed[i] = j;
                }
            });
            grid->addWidget(ansButton[i][j], j / 2, j % 2);
        }
        scrollarea->addWidget(gridWidget);
    }

    this->layout()->addWidget(scrollarea);

    if(question->CheckMedia) {
        this->layout()->addWidget(new MediaPlayerWidget(QString::fromStdString(question->getMediaPath()), this));
    }
}

vector<string> ABCQuestionUI::getUserAns() {
    vector<string> ans(ansChoosed.size());
    for(int i = 0, n = ansChoosed.size(); i < n; ++i) {
        ans[i] = 'A' + ansChoosed[i];
    }
    return ans;
}

bool ABCQuestionUI::validate(std::vector<std::string> result) {
    vector<int> resInt;
    bool ret = true;
    this->setEditAble(false);

    for(int i = 0, n = result.size(); i < n; ++i) {
        resInt.push_back(result[i][0] - 'A');
    }

    for(int i = 0, n = resInt.size(); i < n; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(j != resInt[i] && j != ansChoosed[i]) {
                ansButton[i][j]->setStyleSheet(ConstantGUI::QUESTION_ANS_BUTTON_HIDEN_ANS);
                ret = false;
            }
        }

        if(resInt[i] == ansChoosed[i]) {
            ansButton[i][resInt[i]]->setStyleSheet(ConstantGUI::QUESTION_CORRECT_ANS);
        } else {
            ansButton[i][resInt[i]]->setStyleSheet(ConstantGUI::QUESTION_CORRECT_ANS_S);
            if(ansChoosed[i] >= 0) {
                ansButton[i][ansChoosed[i]]->setStyleSheet(ConstantGUI::QUESTION_WRONG_ANS);
            }
        }
    }


    return ret;
}

void ABCQuestionUI::setEditAble(bool flag) {
    for(const auto x: ansButton) {
        for(const auto y: x) {
            y->setEnabled(flag);
        }
    }
}
