QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

include (../External/json/json.pri)
RC_ICONS = "./resources/icon/appicon.ico"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../BUS/Connection.cpp \
    ../BUS/CoursesManagement.cpp \
    ../BUS/Helper.cpp \
    ../BUS/Session.cpp \
    ../BUS/StringTokenizer.cpp \
    ../BUS/TaskManagement.cpp \
    ../BUS/UserManagement.cpp \
    ../DTO/ABCQuestion.cpp \
    ../DTO/Admin.cpp \
    ../DTO/BlankQuestion.cpp \
    ../DTO/Course.cpp \
    ../DTO/Date.cpp \
    ../DTO/Question.cpp \
    ../DTO/Ranking.cpp \
    ../DTO/TFQuestion.cpp \
    ../DTO/Task.cpp \
    ../DTO/Teacher.cpp \
    ../DTO/Test.cpp \
    ../DTO/User.cpp \
    ../External/md5/md5.cpp \
    AdminTaskPage/AdminTaskPageUI.cpp \
    AppDialog/ChangePasswordUI.cpp \
    AppDialog/ConfirmDialog.cpp \
    AppDialog/MessageDialog.cpp \
    Constant/ConstantGUI.cpp \
    CourseAdvertiseWidget/CoursesAdvertiseWidget.cpp \
    CourseUI/CourseUI.cpp \
    EnglishPracticeUI/PracticeUI.cpp \
    HomeUI/HomeUI.cpp \
    MediaPlayer/MediaPlayerWidget.cpp \
    Misc/WelcomePage.cpp \
    AppDialog/PersonalInformation.cpp \
    AppDialog/ReportFormUI.cpp \
    TeacherTaskPage/TeacherTaskPageUI.cpp \
    TestAdvertiseWidget/TestAdvertiseWidget.cpp \
    TestPage/ABCQuestionUI.cpp \
    TestPage/BlankQuestionUI.cpp \
    TestPage/TFQuestionUI.cpp \
    TestPage/TestPage.cpp \
    UserInformationPage/AddCourseUI.cpp \
    UserInformationPage/RankingRow.cpp \
    UserInformationPage/UserInformationPageUI.cpp \
    VScrollArea/VerticalScrollArea.cpp \
    main.cpp

HEADERS += \
    ../BUS/Connection.h \
    ../BUS/CoursesManagement.h \
    ../BUS/Helper.h \
    ../BUS/Session.h \
    ../BUS/StringTokenizer.h \
    ../BUS/TaskManagement.h \
    ../BUS/UserManagement.h \
    ../DTO/ABCQuestion.h \
    ../DTO/Admin.h \
    ../DTO/BlankQuestion.h \
    ../DTO/Course.h \
    ../DTO/Date.h \
    ../DTO/Question.h \
    ../DTO/Ranking.h \
    ../DTO/TFQuestion.h \
    ../DTO/Task.h \
    ../DTO/Teacher.h \
    ../DTO/Test.h \
    ../DTO/User.h \
    ../External/md5/md5.h \
    AdminTaskPage/AdminTaskPageUI.h \
    AppDialog/ChangePasswordUI.h \
    AppDialog/ConfirmDialog.h \
    AppDialog/MessageDialog.h \
    Constant/ConstantGUI.h \
    CourseAdvertiseWidget/CoursesAdvertiseWidget.h \
    CourseUI/CourseUI.h \
    EnglishPracticeUI/PracticeUI.h \
    HomeUI/HomeUI.h \
    MediaPlayer/MediaPlayerWidget.h \
    Misc/WelcomePage.h \
    AppDialog/PersonalInformation.h \
    AppDialog/ReportFormUI.h \
    TeacherTaskPage/TeacherTaskPageUI.h \
    TestAdvertiseWidget/TestAdvertiseWidget.h \
    TestPage/ABCQuestionUI.h \
    TestPage/BlankQuestionUI.h \
    TestPage/TFQuestionUI.h \
    TestPage/TestPage.h \
    UserInformationPage/AddCourseUI.h \
    UserInformationPage/RankingRow.h \
    UserInformationPage/UserInformationPageUI.h \
    VScrollArea/VerticalScrollArea.h

FORMS += \
    AdminTaskPage/AdminTaskPageUI.ui \
    AppDialog/ChangePasswordUI.ui \
    CourseAdvertiseWidget/CoursesAdvertiseWidget.ui \
    CourseUI/CourseUI.ui \
    EnglishPracticeUI/PracticeUI.ui \
    HomeUI/HomeUI.ui \
    Misc/WelcomePage.ui \
    AppDialog/PersonalInformation.ui \
    AppDialog/ReportFormUI.ui \
    TeacherTaskPage/TeacherTaskPageUI.ui \
    TestAdvertiseWidget/TestAdvertiseWidget.ui \
    TestPage/TestPage.ui \
    UserInformationPage/AddCourseUI.ui \
    UserInformationPage/UserInformationPageUI.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Data/UserData/AdminTaskList.json \
	../Data/UserData/UserData.json \
    resources/Untitled-1.ai \
    resources/courses/default.jpg \
    resources/icon/appicon.ico \
    resources/icon/appicon.png \
    resources/icon/big_default_avt.png \
    resources/icon/default_avt.png \
    resources/icon/favicon.png \
    resources/icon/hand-up.jpg \
    resources/icon/hand-up.png \
    resources/testing_media/Listen9.mp3

RESOURCES += \
    resources.qrc \
