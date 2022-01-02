#include "HomeUI.h"
#include "ui_HomeUI.h"

#include "PracticeUI.h"
#include "UserInformationPageUI.h"
#include "VerticalScrollArea.h"
#include "../BUS/UserManagement.h"
#include "ChangePasswordUI.h"

#include <QBoxLayout>
#include <QAction>
#include <QActionEvent>
#include <QThread>

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    this->setFixedWidth(1302);
    this->setFixedHeight(752);

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
    this->setMenuBar(nullptr);

    this->ui->setupUi(this);

    this->user = nullptr;
    this->initializedView();
    ui->mainPanel->setCurrentIndex(0);
    ui->homePagePanel->setCurrentIndex(0);
}

void Home::initializedView() {
    this->sideBarIndex = 0;
    this->sideBarButtons = new QPushButton*[Home::SIDE_BAR_TABS];
    this->sideBarPushButtonContent = new QString[Home::SIDE_BAR_TABS];

    sideBarPushButtonContent[0] = "Home";
    sideBarPushButtonContent[1] = "Courses";
    sideBarPushButtonContent[2] = "Your Courses";
    sideBarPushButtonContent[3] = "Ranking";

    for(int i = 0; i < Home::SIDE_BAR_TABS; ++i) {
        this->sideBarButtons[i] = new QPushButton(),
        this->sideBarButtons[i]->setFixedWidth(181),
        this->sideBarButtons[i]->setFixedHeight(131),
        this->sideBarButtons[i]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE),
        this->sideBarButtons[i]->setText(sideBarPushButtonContent[i]);

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

    ui->homePagePanel->setStyleSheet(ConstantGUI::BORDER_HOMEPAGE_STYLE);

    homePageContent = new QWidget*[Home::SIDE_BAR_TABS];
    homePageContent[1] = new VerticalScrollArea(2, this);
    homePageContent[0] = new QWidget;
    homePageContent[2] = new QWidget;
    homePageContent[3] = new QWidget;

    coursesAdvertise = new CoursesAdvertise*[10];

    for(int i = 0; i < 10; ++i)
        coursesAdvertise[i] = new CoursesAdvertise(this, 3);

    for(int i = 0; i < 10; ++i) {
        ((VerticalScrollArea*)homePageContent[1])->addWidget(coursesAdvertise[i]);
    }

    this->ui->sideBarFrame->setLayout(new QVBoxLayout);
    for(int i = 0; i < Home::SIDE_BAR_TABS; ++i)
        this->ui->sideBarFrame->layout()->addWidget(sideBarButtons[i]);

    for(int i = 0; i < Home::SIDE_BAR_TABS; ++i)
        this->ui->homePagePanel->insertWidget(i, homePageContent[i]);

    sideBarIndex = 1;
    this->ui->homePagePanel->setCurrentIndex(1);
    sideBarButtons[1]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);

    QPixmap pixmap(":/resources/icon/favicon.png");
    pixmap = pixmap.scaled(ui->favicon->size(),Qt::KeepAspectRatio);
    ui->favicon->setPixmap(pixmap);
    ui->favicon->setVisible(true);

    this->updateNavigation();
    ui->mainPanel->setCurrentIndex(0);
}

Home::~Home()
{
    delete ui;
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

}

void Home::on_sessionInfoBtn_clicked()
{
    if(!this->user)
        this->ui->mainPanel->setCurrentIndex(1),
        this->ui->loginPaneStack->setCurrentIndex(1),
        this->ui->sessionInfoBtn->setVisible(false);
    else this->logout();
}

void Home::on_loginBtn_clicked()
{
    std::string uname = this->ui->loginUnameTxt->text().toStdString();
    std::string password = this->ui->loginPwTxt->text().toStdString();

    this->user = UserManagement::login(uname, password);

    if(this->user)
        this->updateNavigation();
}

void Home::updateNavigation() {
    if(!this->user) {
        ui->avtLbl->setVisible(false);
        ui->sessionCbb->clear();
        ui->sessionCbb->setVisible(false);
        ui->sessionInfoBtn->setVisible(true);
    } else {
        this->ui->sessionInfoBtn->setVisible(false);
        QString placeHolderText = "Welcome " + QString::fromStdString(this->user->getName());

        this->ui->sessionCbb->setCurrentIndex(2);
        this->ui->sessionCbb->setPlaceholderText(placeHolderText);
        this->ui->sessionCbb->setVisible(true);
        this->ui->sessionCbb->addItem("Profile");
        this->ui->sessionCbb->addItem("Logout");

        QPixmap pixmap(":/resources/icon/hand-up.jpg");
        pixmap = pixmap.scaled(ui->avtLbl->size(),Qt::KeepAspectRatio);

        QRegion *region = new QRegion(0, 0, ui->avtLbl->width(), ui->avtLbl->height(), QRegion::Ellipse);
        ui->avtLbl->setStyleSheet(ui->avtLbl->styleSheet() + QString("border-radius: 50%;"));
        ui->avtLbl->setScaledContents(true);
        ui->avtLbl->setMask(*region);
        ui->avtLbl->setPixmap(pixmap);
        this->ui->avtLbl->setVisible(true);

        ui->mainPanel->setCurrentIndex(0);

        cntProfilePage = 4 - (user->getRole() == User::STUDENT);

        profileSideBarButtons = new QPushButton*[cntProfilePage];
        profileSideBarPushButtonContent = new QString[cntProfilePage];

        profileSideBarPushButtonContent[0] = "Information";
        profileSideBarPushButtonContent[1] = "Archievement";
        profileSideBarPushButtonContent[2] = "Your courses";

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

        profilePageContent = new QWidget*[cntProfilePage];
        profilePageContent[0] = new UserInformationPageUI(user, this);
        for(int i = 1; i < cntProfilePage; ++i)
            profilePageContent[i] = new QWidget;

        for(int i = 0; i < cntProfilePage; ++i)
            ui->profilePagePanel->addWidget(profilePageContent[i]);

        profileSideBarIndex = 0;
        profileSideBarButtons[profileSideBarIndex]->setStyleSheet(ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE);
    }
}

void Home::on_signupBtn_clicked()
{
    this->ui->signUpError->clear();
    std::string password = this->ui->signUpPwTxt->text().toStdString();
    std::string password_re = this->ui->signUpPwTxt_re->text().toStdString();

    for(auto x: password) if(x == ' ' || x == '\t') {
        this->ui->signUpError->setText("Password must not be contain white characters");
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
    delete this->user;
    this->user = nullptr;

    for(int i = 0; i < cntProfilePage; ++i)
        delete profileSideBarButtons[i];
    delete[] profileSideBarButtons;

    for(int i = 0; i < cntProfilePage; ++i)
        delete profilePageContent[i];
    delete[] profilePageContent;

    delete[] profileSideBarPushButtonContent;

    this->updateNavigation();
    ui->mainPanel->setCurrentIndex(0);
    ui->homePagePanel->setCurrentIndex(0);
}

void Home::on_sessionCbb_currentIndexChanged(int index)
{
    if(index == 0) {
        this->ui->mainPanel->setCurrentIndex(2);
    }
    else if(index == 1)
        this->logout();

    this->ui->sessionCbb->setCurrentIndex(2);
    QString placeHolderText = user ? "Welcome " + QString::fromStdString(this->user->getName()) : "";
    this->ui->sessionCbb->setPlaceholderText(placeHolderText);
}

void Home::on_backToHomeBtn_clicked()
{
    ui->mainPanel->setCurrentIndex(0);
}

