#include "TFQuestionUI.h"

#include <QLayout>
#include <QLabel>
#include <Constant/ConstantGUI.h>
#include <MediaPlayer/MediaPlayerWidget.h>
#include <VScrollArea/VerticalScrollArea.h>


using std::vector;
using std::string;
using std::pair;

const std::vector<pair<string, string>> TFQuestionUI::_SIGNAL = {{"True", "T"}, {"False", "F"}};

TFQuestionUI::TFQuestionUI(TFQuestion* question, QWidget *parent)
    : QWidget(parent)
{
    this->setLayout(new QVBoxLayout);
    this->question = question;
    int count = question->getSubQuestionCount();
    this->ansButton.assign(count, vector<QPushButton*>(2, nullptr));
    ansChoosed.assign(count, -1);
    this->initialize();
}

TFQuestionUI::~TFQuestionUI() {

}

void TFQuestionUI::initialize() {
    vector<string> subQuestion = question->getQuestionInfo();

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
        gridWidget->setFixedHeight(60);
        QGridLayout* grid = new QGridLayout(gridWidget);

        for(int j = 0; j < 2; ++j) {
            ansButton[i][j] = new QPushButton(QString::fromStdString(TFQuestionUI::_SIGNAL[j].first) ,this);
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

vector<string> TFQuestionUI::getUserAns() {
    vector<string> ans(ansChoosed.size());
    for(int i = 0, n = ansChoosed.size(); i < n; ++i) {
        if(ansChoosed[i] >= 0)
            ans[i] = _SIGNAL[ansChoosed[i]].second;
        else
            ans[i] = "N";
    }
    return ans;
}

void TFQuestionUI::setEditAble(bool flag) {
    for(const auto x: ansButton) {
        for(const auto y: x) {
            y->setEnabled(flag);
        }
    }
}

bool TFQuestionUI::validate(std::vector<std::string> result) {
    vector<int> resInt;
    this->setEditAble(false);
    bool ret = true;
    for(const auto& x: result) {
        for(int i = 0, n = _SIGNAL.size(); i < n; ++i) {
            if(_SIGNAL[i].second == x) {
                resInt.push_back(i);
                break;
            }
        }
    }

    for(int i = 0, n = resInt.size(); i < n; ++i) {
        for(int j = 0; j < 2; ++j) {
            if(j != resInt[i] && j != ansChoosed[i]) {
                ansButton[i][j]->setStyleSheet(ConstantGUI::QUESTION_ANS_BUTTON_HIDEN_ANS);
            }
        }

        if(resInt[i] == ansChoosed[i]) {
            ansButton[i][resInt[i]]->setStyleSheet(ConstantGUI::QUESTION_CORRECT_ANS);
        } else {
            ansButton[i][resInt[i]]->setStyleSheet(ConstantGUI::QUESTION_CORRECT_ANS_S);
            if(ansChoosed[i] >= 0) {
                ret = false;
                ansButton[i][ansChoosed[i]]->setStyleSheet(ConstantGUI::QUESTION_WRONG_ANS);
            }
        }
    }

    return ret;
}
