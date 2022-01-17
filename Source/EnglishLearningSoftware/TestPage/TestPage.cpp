#include "TestPage.h"
#include "ui_TestPage.h"

#include <../BUS/Session.h>
#include <../BUS/Connection.h>
#include <../BUS/Helper.h>

#include <QGraphicsDropShadowEffect>
#include <TestPage/ABCQuestionUI.h>
#include <TestPage/TFQuestionUI.h>
#include <TestPage/BlankQuestionUI.h>
#include <VScrollArea/VerticalScrollArea.h>
#include <Constant/ConstantGUI.h>

#include <AppDialog/ConfirmDialog.h>
#include <MediaPlayer/MediaPlayerWidget.h>

#include <QDialog>
#include <QLayout>

#include <QTime>

TestPage::TestPage(Course course, int testIndex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPage)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setFixedWidth(1302);
    this->setFixedHeight(752);

    this->testIndex = testIndex;

    test = new Test();
    test->setRating(course.getDifficulty());
    course.LoadTest(*test, testIndex);
    questions = test->getQuestionList();

    userAns.assign(questions.size(), "");
    pushButton.assign(test->questionCount(), nullptr);
    slide.assign(test->questionCount(), nullptr);

    ui->setupUi(this);
    ui->courseName->setText(QString::fromStdString(Helper::toUpper(course.getName())));
    ui->timer->setText(QTime::currentTime().toString("hh : mm : ss"));
    initialize();

    submitFlag = false;
}

void TestPage::initialize() {
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);
    effect->setColor(QColor(68, 68, 68));
    effect->setBlurRadius(30);
    this->ui->rightSideBar->setGraphicsEffect(effect);

    Session* session = Session::getInstance();
    User* user = session->getUserAttempt();

    if(user) {
        ui->name->setText(QString::fromStdString(user->getName()));
        QString _roleStr = QString::fromStdString(user->getRole() == User::ADMIN ? "Admin": (user->getRole() == User::TEACHER ? "Teacher" : "Student"));
        ui->role->setText(_roleStr);
    }

    ui->test->setText(QString::fromStdString(test->getName()));

    QPixmap pixmap(":/resources/icon/default_avt.png");
    pixmap = pixmap.scaled(ui->avtLbl->size(), Qt::KeepAspectRatio);
    ui->avtLbl->setPixmap(pixmap);

    ui->questionChooser->setLayout(new QVBoxLayout);
    VerticalScrollArea* scrollarea = new VerticalScrollArea(1, this);

    for(int i = 0, n = questions.size(); i < n; ++i) {
        pushButton[i] = new QPushButton(QString::fromStdString(std::to_string(i)), this);
        pushButton[i]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
        pushButton[i]->setFixedHeight(40);
        scrollarea->addWidget(pushButton[i]);

        if(questions[i]->getType() == Question::ABC_QUESTION) {
            slide[i] = new ABCQuestionUI((ABCQuestion*)questions[i], this);
        } else if(questions[i]->getType() == Question::TF_QUESTION) {
            slide[i] = new TFQuestionUI((TFQuestion*)questions[i], this);
        } else {
            slide[i] = new BlankQuestionUI((BlankQuestion*)questions[i], this);
        }

        ui->questionSlideShow->addWidget(slide[i]);

        connect(pushButton[i], &QPushButton::clicked, [this, i] {
            if(i != currentQuestion) {
                QString tag = "Question " + QString::number(i) + ": " + QString::fromStdString(questions[i]->getIntro());
                ui->questionTag->setText(tag);
                pushButton[currentQuestion]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
                ui->questionSlideShow->setCurrentIndex(i);
                pushButton[i]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
                currentQuestion = i;
            }
        });
    }

    ui->questionChooser->layout()->addWidget(scrollarea);
    currentQuestion = 0;
    if(questions.size())
        pushButton[0]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);

    ui->label_2->setText("There're " + QString::number(questions.size()) + " question(s).");

    QTimer* sysTime = new QTimer(this);
    connect(sysTime, SIGNAL(timeout()), this, SLOT(updateTimer()));
    sysTime->start(1000);
}

void TestPage::updateTimer() {
    ui->timer->setText(QTime::currentTime().toString("hh : mm : ss"));
}

TestPage::~TestPage()
{
    delete test;

    delete ui;
}

void TestPage::on_pushButton_clicked()
{
    if(submitFlag) {
        QDialog* confirmDialog = new ConfirmDialog("Exit this test?");
        int execResult = confirmDialog->exec();

        if(execResult == QDialog::Accepted)
            this->close();

        return;
    }

    vector<vector<string>> testAns(questions.size());

    for(int i = 0, n = questions.size(); i < n; ++i) {
        if(questions[i]->getType() == Question::ABC_QUESTION) {
            testAns[i] = ((ABCQuestionUI*)ui->questionSlideShow->widget(i))->getUserAns();
        } else if(questions[i]->getType() == Question::TF_QUESTION) {
            testAns[i] = ((TFQuestionUI*)ui->questionSlideShow->widget(i))->getUserAns();
        } else {
            testAns[i] = ((BlankQuestionUI*)ui->questionSlideShow->widget(i))->getUserAns();
        }
    }

    std::pair<int, int> result = test->CalResult(testAns);
    CoursesManagement::updateCurrenScore(result.first,this->testIndex);
    User* user = Session::getInstance()->getUserAttempt();

    int dRating = test->RatingChange(user->getRating(),result);
    std::cerr << "old rating: " << user->getRating() << "\n" << "rating change: " << dRating << "\n";
    user->setRating(user->getRating() + dRating);
    std::cerr << "new rating: " << user->getRating() << "\n";

    QDialog* dialog = new ConfirmDialog("Your score is " + QString::number(result.first) + " / " + QString::number(result.second) + ".\n"
                                        + "Rating Change:" + QString::number(dRating) + "\n"
                                        + "Do you want to see your result?");

    int dialog_result = dialog->exec();
    if(dialog_result == QDialog::Accepted) {
        this->showDetails();
    }

    submitFlag = true;
    ui->pushButton->setText("Close");
}

void TestPage::showDetails() {
    vector<vector<string>> result = test->getResult();

    for(int i = 0, n = result.size(); i < n; ++i) {
        bool res = true;

        if(questions[i]->getType() == Question::ABC_QUESTION) {
            res = ((ABCQuestionUI*)ui->questionSlideShow->widget(i))->validate(result[i]);
        } else if(questions[i]->getType() == Question::TF_QUESTION) {
            res = ((TFQuestionUI*)ui->questionSlideShow->widget(i))->validate(result[i]);
        } else {
            res = ((BlankQuestionUI*)ui->questionSlideShow->widget(i))->validate(result[i]);
        }

        if(res) {
        } else pushButton[i]->setText(pushButton[i]->text() + "*");
    }
}
