/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QWidget *centralwidget;
    QFrame *LoginPane;
    QPushButton *loginButton;
    QLabel *labelLoginPane;
    QLineEdit *password;
    QLineEdit *username;
    QFrame *frame;
    QLabel *titleLabel;
    QLabel *sloganTitle;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QMainWindow *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName(QString::fromUtf8("Home"));
        Home->setWindowModality(Qt::ApplicationModal);
        Home->setEnabled(true);
        Home->resize(974, 521);
        Home->setContextMenuPolicy(Qt::NoContextMenu);
        Home->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0.006, stop:0 rgba(32, 5, 43, 255), stop:1 rgba(255, 255, 255, 255)); border-radius: 10px;"));
        Home->setTabShape(QTabWidget::Rounded);
        Home->setDockNestingEnabled(true);
        centralwidget = new QWidget(Home);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        LoginPane = new QFrame(centralwidget);
        LoginPane->setObjectName(QString::fromUtf8("LoginPane"));
        LoginPane->setGeometry(QRect(20, 20, 341, 471));
        LoginPane->setAutoFillBackground(false);
        LoginPane->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:reflect, x1:0.461, y1:1, x2:0.489, y2:0.00527273, stop:0 rgba(43, 18, 67, 255), stop:1 rgba(255, 255, 255, 40));\n"
"border-radius: 15px;"));
        LoginPane->setFrameShape(QFrame::NoFrame);
        LoginPane->setFrameShadow(QFrame::Sunken);
        loginButton = new QPushButton(LoginPane);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(100, 290, 121, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(24);
        font.setBold(true);
        font.setKerning(true);
        loginButton->setFont(font);
        loginButton->setStyleSheet(QString::fromUtf8("border: .1px; border-radius: 3px;"));
        loginButton->setText(QString::fromUtf8("Go!"));
        loginButton->setAutoDefault(false);
        labelLoginPane = new QLabel(LoginPane);
        labelLoginPane->setObjectName(QString::fromUtf8("labelLoginPane"));
        labelLoginPane->setGeometry(QRect(70, 100, 181, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Georgia")});
        font1.setPointSize(32);
        font1.setBold(true);
        labelLoginPane->setFont(font1);
        labelLoginPane->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"text-color: rgba(0, 0, 0, 255);"));
        labelLoginPane->setFrameShape(QFrame::NoFrame);
        labelLoginPane->setFrameShadow(QFrame::Plain);
        labelLoginPane->setAlignment(Qt::AlignCenter);
        labelLoginPane->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        password = new QLineEdit(LoginPane);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(60, 240, 211, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Courier")});
        font2.setPointSize(10);
        font2.setBold(true);
        password->setFont(font2);
        password->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 24); border-radius: 2px;"));
        password->setEchoMode(QLineEdit::Password);
        username = new QLineEdit(LoginPane);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(60, 200, 211, 31));
        username->setFont(font2);
        username->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 24); border-radius: 2px;"));
        username->setEchoMode(QLineEdit::Normal);
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(430, 20, 521, 471));
        frame->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:reflect, x1:0.461, y1:1, x2:0.489, y2:0.00527273, stop:0 rgba(43, 18, 67, 30), stop:1 rgba(255, 255, 255, 30));\n"
"border-radius: 15px;;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        titleLabel = new QLabel(frame);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(10, 10, 511, 81));
        titleLabel->setFont(font1);
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        sloganTitle = new QLabel(frame);
        sloganTitle->setObjectName(QString::fromUtf8("sloganTitle"));
        sloganTitle->setGeometry(QRect(150, 70, 231, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Courier")});
        font3.setPointSize(10);
        sloganTitle->setFont(font3);
        sloganTitle->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        sloganTitle->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 170, 241, 221));
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(320, 260, 181, 171));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Terminal")});
        label_4->setFont(font4);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(240, 120, 181, 171));
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        sloganTitle->raise();
        label_4->raise();
        label_5->raise();
        label_3->raise();
        titleLabel->raise();
        Home->setCentralWidget(centralwidget);

        retranslateUi(Home);

        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QMainWindow *Home)
    {
        Home->setWindowTitle(QCoreApplication::translate("Home", "English Learning Software", nullptr));
        labelLoginPane->setText(QCoreApplication::translate("Home", "LOGIN", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("Home", "Password", nullptr));
        username->setPlaceholderText(QCoreApplication::translate("Home", "Username", nullptr));
        titleLabel->setText(QCoreApplication::translate("Home", "DODEPTRAI-Learning", nullptr));
        sloganTitle->setText(QCoreApplication::translate("Home", "Where's your brain?", nullptr));
        label_3->setText(QCoreApplication::translate("Home", "English is easy!", nullptr));
        label_4->setText(QCoreApplication::translate("Home", "dotran dep trai vl", nullptr));
        label_5->setText(QCoreApplication::translate("Home", "Quick test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
