#include "HomeUI.h"
#include "ui_HomeUI.h"

#include <EnglishPracticeUI/PracticeUI.h>
#include <UserInformationPage/UserInformationPageUI.h>
#include <VScrollArea/VerticalScrollArea.h>
#include <Constant/ConstantGUI.h>
#include <AppDialog/ChangePasswordUI.h>
#include <UserInformationPage/RankingRow.h>

#include <../BUS/UserManagement.h>
#include <../DTO/Ranking.h>

#include <QBoxLayout>
#include <QAction>
#include <QActionEvent>
#include <QThread>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

#include <AppDialog/ConfirmDialog.h>
#include <CourseAdvertiseWidget/CoursesAdvertiseWidget.h>
#include <MediaPlayer/MediaPlayerWidget.h>
#include <TeacherTaskPage/TeacherTaskPageUI.h>
#include <AdminTaskPage/AdminTaskPageUI.h>
#include <Misc/WelcomePage.h>

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    this->setFixedWidth(1302);
    this->setFixedHeight(752);

    this->window()->setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(windowFlags() & (~Qt::WindowMaximizeButtonHint));
    this->setMenuBar(nullptr);

    this->ui->setupUi(this);
    this->initializedView();
    ui->mainPanel->setCurrentIndex(0);
    ui->homePagePanel->setCurrentIndex(0);

    ui->timer->setText(QTime::currentTime().toString("hh : mm : ss"));
}

void Home::renderMainPage() {
    this->sideBarButtons.assign(Home::SIDE_BAR_TABS, nullptr);

    vector<QString> sideBarPushButtonContent(Home::SIDE_BAR_TABS);
    sideBarPushButtonContent[0] = "Home";
    sideBarPushButtonContent[1] = "Courses";
    sideBarPushButtonContent[2] = "Recommend";
    sideBarPushButtonContent[3] = "Ranking";

    ui->homePagePanel->setStyleSheet(ConstantGUI::BORDER_HOMEPAGE_STYLE);
    homePageContent.assign(Home::SIDE_BAR_TABS, nullptr);

    homePageContent[1] = new VerticalScrollArea(2, this);
    homePageContent[2] = new QWidget(homePageContent[2]); // *
    homePageContent[0] = new WelcomePage(this); // *

    for(int i = 0; i < Home::SIDE_BAR_TABS; ++i) {
        this->sideBarButtons[i] = new QPushButton(sideBarPushButtonContent[i], this);
        this->sideBarButtons[i]->setFixedSize(181, 120);
        this->sideBarButtons[i]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE),

        connect(sideBarButtons[i], &QPushButton::clicked, [this, i] {
                if(i != sideBarIndex) {
                    sideBarButtons[sideBarIndex]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
                    sideBarButtons[i]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
                    ui->homePagePanel->setCurrentIndex(i);
                    sideBarIndex = i;
                }
            }
        );
    }

    Session* session = Session::getInstance();
    vector<Course> courseList = session->getAllcourse();
    vector<CoursesAdvertise*> coursesAdvertise(courseList.size(), nullptr);

    QLabel* label = new QLabel("You have to login to see more information" ,this);
    label->setStyleSheet(ConstantGUI::QUESTION_STATEMENT_STYLE_2);
    homePageContent[2]->setLayout(new QVBoxLayout);
    homePageContent[2]->layout()->addWidget(label);

    for(int i = 0, n = courseList.size(); i < n; ++i) {
        coursesAdvertise[i] = new CoursesAdvertise(courseList[i], this),
        ((VerticalScrollArea*)homePageContent[1])->addWidget(coursesAdvertise[i]);
    }

    // build ranking page;
    vector<User> userList = UserManagement::userList();
    vector<vector<string>> table(userList.size());

    for(int i = 0, n = userList.size(); i < n; ++i) {
        table[i].push_back(userList[i].getUserName());
        table[i].push_back(userList[i].getRole() == User::ADMIN ? "Admin"
                                                                : (userList[i].getRole() == User::TEACHER ? "Teacher" : "Student"));
        table[i].push_back(userList[i].getDayOfBirth().toString());
        table[i].push_back(std::to_string(userList[i].getRating()));
    }

    Ranking ranking(table, 3, [&](string a, string b) -> bool {
        int _a = std::stoi(a), _b = std::stoi(b);
        return _a != _b ? _a > _b : a > b;
    });

    table = ranking.getTable();

    table.insert(table.begin(), {"User name", "Role", "Day of birth", "Rating"});

    homePageContent[3] = new QWidget(this);
    homePageContent[3]->setLayout(new QVBoxLayout);
    homePageContent[3]->layout()->setAlignment(Qt::AlignHCenter);
    homePageContent[3]->setFixedSize(ui->homePagePanel->size());

    for(int i = 0, n = table.size(); i < n; ++i) {
        if(i)
            homePageContent[3]->layout()->addWidget(new RankingRow(std::to_string(i), table[i], this));
        else
            homePageContent[3]->layout()->addWidget(new RankingRow("", table[i], this));
    }

    sideBarIndex = 0;
    this->ui->homePagePanel->setCurrentIndex(0);
    sideBarButtons[0]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);

    // add sideBar button and main page
    this->ui->sideBarFrame->setLayout(new QVBoxLayout);
    for(int i = 0; i < Home::SIDE_BAR_TABS; ++i) {
        this->ui->sideBarFrame->layout()->addWidget(sideBarButtons[i]);
        this->ui->homePagePanel->addWidget(homePageContent[i]);
    }

    QPixmap pixmap(":/resources/icon/favicon.png");
    pixmap = pixmap.scaled(ui->favicon->size(),Qt::KeepAspectRatio);
    ui->favicon->setPixmap(pixmap);
    ui->favicon->setVisible(true);
}

void Home::initializedView() {
    // add effect to some widget
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(ui->navigatorBar);
    effect->setOffset(5, 5);
    effect->setColor(QColor(68, 68, 68));
    effect->setBlurRadius(30);
    ui->navigatorBar->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect* effect1 = new QGraphicsDropShadowEffect(ui->rightSideBar);
    effect1->setOffset(0, 0);
    effect1->setColor(QColor(68, 68, 68));
    effect1->setBlurRadius(8);
    ui->sideBarFrame->setGraphicsEffect(effect1);

    QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect(ui->rightSideBar);
    effect2->setOffset(0, 0);
    effect2->setColor(QColor(68, 68, 68));
    effect2->setBlurRadius(8);
    ui->sideBarProfile->setGraphicsEffect(effect2);

    QGraphicsDropShadowEffect* effect3 = new QGraphicsDropShadowEffect(ui->rightSideBar);
    effect3->setOffset(0, 0);
    effect3->setColor(QColor(68, 68, 68));
    effect3->setBlurRadius(30);
    ui->rightSideBar->setGraphicsEffect(effect3);

    this->renderMainPage();
    this->updateSession();

    ui->mainPanel->setCurrentIndex(0);
    this->sideBarIndex = 0;

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000 * 60);
}

Home::~Home()
{
    Session::invalidate();
}

void Home::on_newaccountBtn_clicked()
{
    this->ui->loginPaneStack->setCurrentIndex(0);
}

void Home::on_cancelCreateBtn_clicked()
{
    this->ui->loginPaneStack->setCurrentIndex(1);
}

void Home::on_loginShowPwCBx_stateChanged(int arg1)
{
    if(this->ui->loginShowPwCBx->checkState() == Qt::Checked)
        this->ui->loginPwTxt->setEchoMode(QLineEdit::Normal);
    else
        this->ui->loginPwTxt->setEchoMode(QLineEdit::Password);
}

void Home::on_signUpCBx_stateChanged(int arg1)
{
    if(this->ui->signUpCBx->checkState() == Qt::Checked)
        this->ui->signUpPwTxt->setEchoMode(QLineEdit::Normal);
    else
        this->ui->signUpPwTxt->setEchoMode(QLineEdit::Password);
}

void Home::updateCoursesPage() {
    ui->timer->setText(QTime::currentTime().toString("hh : mm : ss"));
}

void Home::on_sessionInfoBtn_clicked()
{
    User* user = Session::getInstance()->getUserAttempt();
    if(!user) {
        this->ui->mainPanel->setCurrentIndex(1),
        this->ui->loginPaneStack->setCurrentIndex(1),
        this->ui->sessionInfoBtn->setVisible(false);
    }
    else this->logout();
}

void Home::on_loginBtn_clicked()
{
    ui->loginError->clear();
    std::string uname = this->ui->loginUnameTxt->text().toStdString();
    std::string password = this->ui->loginPwTxt->text().toStdString();

    bool result = Session::getInstance()->login(uname, password);

    if(result) {
        this->updateSession();
        if(!ui->savePass->isChecked())
            ui->loginUnameTxt->clear(),
            ui->loginPwTxt->clear();
    }
    else {
        ui->loginError->setText("Login failed");
    }
}

void Home::updateTimer() {
    ui->timer->setText(QTime::currentTime().toString("hh : mm"));
}

void Home::updateSession() {
    User* user = Session::getInstance()->getUserAttempt();
    if(!user) {
        ui->avtLbl->setVisible(false);
        ui->sessionCbb->clear();
        ui->sessionCbb->setVisible(false);
        ui->sessionInfoBtn->setVisible(true);

        delete homePageContent[2];
        homePageContent[2] = new QWidget(this);
        ui->homePagePanel->insertWidget(2, homePageContent[2]);

        homePageContent[2]->setLayout(new QHBoxLayout);
        homePageContent[2]->layout()->addWidget(new QLabel("Login to continue", homePageContent[2]));

        ui->rsb_name->setVisible(false);
        ui->avtLbl_2->setVisible(false);
        ui->rsb_role->setVisible(false);
        ui->rsb_rating->setVisible(false);
    } else {
        ui->rsb_name->setText(QString::fromStdString(user->getName()));
        ui->rsb_role->setText(user->getRole() == User::ADMIN ? "ADMIN" : (User::TEACHER ? "TEACHER" : "STUDENT"));
        ui->rsb_rating->setText("Rating: " + QString::number(user->getRating()));;

        ui->rsb_name->setVisible(true);
        ui->rsb_role->setVisible(true);
        ui->rsb_rating->setVisible(true);

        this->ui->sessionInfoBtn->setVisible(false);

        QString placeHolderText = "Welcome " + QString::fromStdString(user->getName());
        this->ui->sessionCbb->setCurrentIndex(2);
        this->ui->sessionCbb->setPlaceholderText(placeHolderText);
        this->ui->sessionCbb->setVisible(true);
        this->ui->sessionCbb->addItems({"Profile", "Logout"});

        QPixmap pixmap(":/resources/icon/default_avt.png");
        pixmap = pixmap.scaled(ui->avtLbl->size(),Qt::KeepAspectRatio);

        QRegion region(0, 0, ui->avtLbl->width(), ui->avtLbl->height(), QRegion::Ellipse);
        QRegion region_2(0, 0, ui->avtLbl_2->width(), ui->avtLbl_2->height(), QRegion::Ellipse);
        ui->avtLbl->setStyleSheet(ui->avtLbl->styleSheet() + QString("border-radius: 50%;"));
        ui->avtLbl->setScaledContents(true);
        ui->avtLbl->setMask(region);

        ui->avtLbl_2->setStyleSheet(ui->avtLbl->styleSheet() + QString("border-radius: 50%;"));
        ui->avtLbl_2->setScaledContents(true);

        QPixmap _pixmap(":/resources/icon/default_avt.png");
        _pixmap = _pixmap.scaled(ui->avtLbl_2->size(),Qt::KeepAspectRatio);
        ui->avtLbl_2->setPixmap(_pixmap);
        ui->avtLbl_2->setMask(region_2);
        ui->avtLbl->setPixmap(pixmap);
        ui->avtLbl->setVisible(true);
        ui->avtLbl_2->setVisible(true);

        ui->mainPanel->setCurrentIndex(0);

        cntProfilePage = 4 - (user->getRole() == User::STUDENT);

        profilePageContent.assign(cntProfilePage, nullptr);
        profileSideBarButtons.assign(cntProfilePage, nullptr);
        vector<QString> profileSideBarPushButtonContent(cntProfilePage);

        profileSideBarPushButtonContent[0] = "Information";
        profileSideBarPushButtonContent[1] = "Achievement";
        profileSideBarPushButtonContent[2] = "Your courses";

        Session* session = Session::getInstance();

        vector<Course> recommend = session->getRecommend();
        vector<Course> uCourse = session->getUsercourse();

        vector<CoursesAdvertise*> recommendUI(recommend.size(), nullptr);
        vector<CoursesAdvertise*> uCourseUI(uCourse.size(), nullptr);

        delete homePageContent[2];
        homePageContent[2] = new VerticalScrollArea(2, ui->homePagePanel);
        ui->homePagePanel->insertWidget(2, homePageContent[2]);

        for(int i = 0, n = recommend.size(); i < n; ++i) {
            recommendUI[i] = new CoursesAdvertise(recommend[i], this);
            ((VerticalScrollArea*)homePageContent[2])->addWidget(recommendUI[i]);
        }

        profilePageContent[2] = new VerticalScrollArea(2, ui->homePagePanel);
        for(int i = 0, n = uCourse.size(); i < n; ++i) {
            uCourseUI[i] = new CoursesAdvertise(uCourse[i], profilePageContent[2]);
            ((VerticalScrollArea*)profilePageContent[2])->addWidget(uCourseUI[i]);
        }

        if(user->getRole() != User::STUDENT) {
            if(user->getRole() == User::ADMIN)
                profileSideBarPushButtonContent[3] = "Admin task";
            else if(user->getRole() == User::TEACHER)
                profileSideBarPushButtonContent[3] = "Add new courses";
        }

        ui->sideBarProfile->setLayout(new QVBoxLayout);
        for(int i = 0; i < cntProfilePage; ++i) {
            profileSideBarButtons[i] = new QPushButton;
            profileSideBarButtons[i]->setFixedWidth(181);
            profileSideBarButtons[i]->setFixedHeight(110);
            profileSideBarButtons[i]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
            profileSideBarButtons[i]->setText(profileSideBarPushButtonContent[i]);
            ui->sideBarProfile->layout()->addWidget(profileSideBarButtons[i]);
        }

        for(int i = 0; i < cntProfilePage; ++i) {
            connect(profileSideBarButtons[i], &QPushButton::clicked, [this, i] {
                if(i != profileSideBarIndex) {
                    profileSideBarButtons[profileSideBarIndex]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
                    profileSideBarButtons[i]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
                    ui->profilePagePanel->setCurrentIndex(i);
                    profileSideBarIndex = i;
                }
            });
        }

        profilePageContent[0] = new UserInformationPageUI(ui->profilePagePanel);
        profilePageContent[1] = new QWidget();
        profilePageContent[1]->setLayout(new QVBoxLayout);
        QPixmap pending_pixmap(":/resources/icon/pending_function.png");
        QLabel* label = new QLabel(profilePageContent[1]);
        label->setPixmap(pending_pixmap);
        profilePageContent[1]->layout()->addWidget(label);

        if(user->getRole() == User::TEACHER) {
            profilePageContent[3] = new TeacherTaskPageUI(this);
        } else if(user->getRole() == User::ADMIN) {
            profilePageContent[3] = new AdminTaskPageUI(this);
        }

        for(int i = 0; i < cntProfilePage; ++i)
            ui->profilePagePanel->addWidget(profilePageContent[i]);

        profileSideBarIndex = 0;
        ui->profilePagePanel->setCurrentIndex(0);
        profileSideBarButtons[profileSideBarIndex]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
    }
}

void Home::on_signupBtn_clicked()
{
    this->ui->signUpError->clear();
    std::string password = this->ui->signUpPwTxt->text().toStdString();
    std::string password_re = this->ui->signUpPwTxt_re->text().toStdString();

    for(auto x: password) if(x == ' ' || x == '\t') {
        this->ui->signUpError->setText("Password must not contain white characters");
        return;
    }

    if(password != password_re) {
        this->ui->signUpError->setText("Password does not match");
        return;
    }

    std::string username = this->ui->signUpUname->text().toStdString();
    for(char x: username) if(x == ' ') {
        this->ui->signUpError->setText("Username must not be contain white characters");
        return;
    }

    if(UserManagement::signUp(username, password)) {

    } else {
        this->ui->signUpError->setText("Account is already existed");
        return;
    }

    this->ui->loginPaneStack->setCurrentIndex(1);
}

void Home::on_cancelLoginBtn_clicked()
{
    this->ui->mainPanel->setCurrentIndex(0);
    this->ui->sessionInfoBtn->setVisible(true);
}

void Home::logout() {

    QDialog* dialog = new ConfirmDialog("Do you want to leave?");
    int dialogResult = dialog->exec();

    if(dialogResult == QDialog::Rejected) {
        return;
    }

    Session::getInstance()->logout();

    for(int i = 0; i < cntProfilePage; ++i)
        delete profileSideBarButtons[i];
    profileSideBarButtons.clear();

    for(int i = 0; i < cntProfilePage; ++i)
        delete profilePageContent[i];

    profilePageContent.clear();

    this->updateSession();

    ui->mainPanel->setCurrentIndex(1);

    ui->homePagePanel->setCurrentIndex(0);
    sideBarIndex = 0;

    this->ui->sessionInfoBtn->setVisible(false);
}

void Home::on_sessionCbb_currentIndexChanged(int index)
{
    if(index == 0) {
        this->ui->mainPanel->setCurrentIndex(2);
    }
    else if(index == 1)
        this->logout();

    User* user = Session::getInstance()->getUserAttempt();
    this->ui->sessionCbb->setCurrentIndex(2);
    QString placeHolderText = user ? "Welcome " + QString::fromStdString(user->getName()) : "";
    this->ui->sessionCbb->setPlaceholderText(placeHolderText);
}

void Home::on_backToHomeBtn_clicked()
{
    ui->mainPanel->setCurrentIndex(0);

    sideBarButtons[sideBarIndex]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE);
    sideBarIndex= 0;
    ui->homePagePanel->setCurrentIndex(0);
    sideBarButtons[sideBarIndex]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
}

