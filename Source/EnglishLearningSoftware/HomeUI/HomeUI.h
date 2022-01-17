#ifndef HOMEUI_H
#define HOMEUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QFrame>

#include <../DTO/User.h>
#include <../BUS/Session.h>

#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_newaccountBtn_clicked();

    void on_cancelCreateBtn_clicked();

    void on_loginShowPwCBx_stateChanged(int arg1);

    void on_signUpCBx_stateChanged(int arg1);

    void on_sessionInfoBtn_clicked();

    void on_loginBtn_clicked();

    void on_signupBtn_clicked();

    void on_cancelLoginBtn_clicked();

    void on_sessionCbb_currentIndexChanged(int index);

    void on_backToHomeBtn_clicked();

private:
    void updateCoursesPage();

    void initializedView();

    void renderMainPage();

    // theses two function to handle user session
    void updateSession();
    void logout();

protected slots:
    void updateTimer();

private:
    Ui::Home *ui;

private:
    static const int SIDE_BAR_TABS = 4;

private:
    //component

    //for side bar and content tab - home tab
    int sideBarIndex;
    int cntHomePage;
    std::vector<QPushButton*> sideBarButtons;
    std::vector<QWidget*> homePageContent;

    //for user profile
    int profileSideBarIndex;
    int cntProfilePage;
    std::vector<QPushButton*> profileSideBarButtons;
    std::vector<QWidget*> profilePageContent;
};
#endif // HOMEUI_H
