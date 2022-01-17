#include "BlankQuestionUI.h"

#include <QLabel>
#include <QLayout>
#include <VScrollArea/VerticalScrollArea.h>
#include <Constant/ConstantGUI.h>
#include <MediaPlayer/MediaPlayerWidget.h>

BlankQuestionUI::BlankQuestionUI(BlankQuestion* question, QWidget *parent)
    : QWidget(parent)
{
    this->question = question;
    ansEditBox.assign(question->blankCount(), nullptr);
    this->initialize();
}

BlankQuestionUI::~BlankQuestionUI() {

}

void BlankQuestionUI::initialize() {
    int blCount = question->blankCount();
    this->setLayout(new QVBoxLayout);

    VerticalScrollArea* scrollarea = new VerticalScrollArea(1, this);
    scrollarea->setStyleSheet(ConstantGUI::VERTICAL_SCROLL_STYLE_S);
    QString paragraph = QString::fromStdString(question->getParagraph());
    QLabel* paragraph_label = new QLabel(paragraph, scrollarea);
    paragraph_label->setWordWrap(true);
    paragraph_label->setStyleSheet(ConstantGUI::QUESTION_STATEMENT_STYLE_2);
    layout()->addWidget(paragraph_label);

    if(blCount) {
        QLabel* require = new QLabel("Let's fill the blank!", this);
        require->setStyleSheet(ConstantGUI::QUESTION_STATEMENT_STYLE_2);
        scrollarea->addWidget(require);
    }

    for(int i = 0; i < blCount; ++i) {
        this->ansEditBox[i] = new QLineEdit(this);
        this->ansEditBox[i]->setStyleSheet(ConstantGUI::BLANK_QUESTION_STYLE);

        this->ansEditBox[i]->setFixedHeight(40);
        QWidget* layoutWidget = new QWidget(this);
        layoutWidget->setFixedHeight(50);

        layoutWidget->setLayout(new QHBoxLayout);
        QLabel* label = new QLabel(QString::number(i + 1) + ": ", this);
        label->setStyleSheet(ConstantGUI::QUESTION_STATEMENT_STYLE_2);
        layoutWidget->layout()->addWidget(label);
        layoutWidget->layout()->addWidget(ansEditBox[i]);
        scrollarea->addWidget(layoutWidget);
    }

    this->layout()->addWidget(scrollarea);

    if(question->CheckMedia) {
        this->layout()->addWidget(new MediaPlayerWidget(QString::fromStdString(question->getMediaPath()), this));
    }
}

vector<string> BlankQuestionUI::getUserAns() {
   vector<string> result;
   for(const auto& x: ansEditBox) {
       result.push_back(x->text().toStdString());
   }
   return result;
}

bool BlankQuestionUI::validate(std::vector<std::string> result) {
    this->setEditAble(false);
    bool ret = true;
    for(int i = 0, n = result.size(); i < n; ++i) {
        QString userWritten = ansEditBox[i]->text();
        QString ans = QString::fromStdString(result[i]);
        if(userWritten != ans) {
            ret = false;
            QString hehe = userWritten + "\t→\t" + ans;
            ansEditBox[i]->setText(hehe);
            ansEditBox[i]->setStyleSheet(ConstantGUI::BLANK_QUESTION_WRONG_ANS);
        } else {
            ansEditBox[i]->setStyleSheet(ConstantGUI::BLANK_QUESTION_CORRECT_ANS);
        }
    }
    return ret;
}

void BlankQuestionUI::setEditAble(bool flag) {
    for(const auto& x: ansEditBox)
        x->setEnabled(flag);
}

