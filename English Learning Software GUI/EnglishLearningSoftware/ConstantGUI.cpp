#include "ConstantGUI.h"

const QString ConstantGUI::VERTICAL_SCROLL_STYLE = QString("\
       QScrollArea {\
           border: none;\
       }\
       QScrollBar {\
           background: rgb(128, 128, 128);\
       }\
       QScrollBar:vertical {\
           width: 13px;\
           border-radius: 5px;\
       }\
       QScrollBar::handle {\
           background: rgb(97, 31, 31);\
       }\
       QScrollBar::handle:vertical {\
           width: 10px;\
           min-height: 10px;\
       }"
);


const QString ConstantGUI::PUSH_BUTTON_WITH_HOVER_STYLE = QString("\
      QPushButton {\
          background-color: #405cf5;\
          color: #fff; \
          border-radius: 6px;\
      } \
      QPushButton:hover { \
          background-color: rgb(55, 45, 135);\
      }\
      QPushButton:hover:!pressed{\
          border: 1.5px solid rgb(50, 45, 50);\
      }"
);

const QString ConstantGUI::ADVERTISE_DEMO_FORM_STYLE = QString("\
    CoursesAdvertiseWidget{\
        border: 1px solid black; \
        border-radius: 10px;\
        background-color: rgba(230, 230, 230);\
    }\
    QLabel {\
        background-color: grba(0,0,0,0);\
    }\
");

const QString ConstantGUI::LINE_PUSH_BUTTON_HOVER_STYLE = QString("\
     QPushButton {\
         background-color: rgba(0, 0, 0, 0);\
         color: black; \
     } \
     QPushButton:hover { \
         color: rgb(128, 200, 168);\
     }\
     QPushButton:hover:!pressed{\
         color: rgb(128, 200, 168);\
     }"
);

const QString ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_STYLE = QString("\
  QPushButton {\
     background-color: rgba(230, 230,230,230);\
     border-radius: 12px;  color: #121212;\
     font-family: Inter,sans-serif;\
     font-size: 1.2rem;\
     font-weight: 700;\
     line-height: 1;\
     margin: 0;\
     outline: none;\
     padding: 1rem 1.2rem;\
     text-align: center;\
     text-decoration: none;\
     white-space: nowrap;\
     border: 0;\
  }\
  QPushButton:hover:!pressed\
  {\
    border: 1.5px solid rgb(55, 45, 135);\
  }\
    QPushButton:hover {\
  }"
);

const QString ConstantGUI::SIDE_BAR_PUSH_BUTTON_HOVER_CLICKED_STYLE = QString("\
  QPushButton {\
     background-color: rgb(45, 18, 153);\
     border-radius: 12px;  color: #fff;\
     font-family: Inter,sans-serif;\
     font-size: 1.2rem;\
     font-weight: 700;\
     line-height: 1;\
     margin: 0;\
     outline: none;\
     padding: 1rem 1.2rem;\
     text-align: center;\
     text-decoration: none;\
     white-space: nowrap;\
     border: 0;\
  }"
);

const QString ConstantGUI::BORDER_HOMEPAGE_STYLE = QString("\
QWidget {\
    border-radius: 15px;\
}");

const QString ConstantGUI::LINE_EDIT_READ_ONLY = QString("\
    QLineEdit {\
        border: 0px;\
        border-radius: 3px;\
        background-color: rgba(0, 0, 0, 0);\
    }\
");

const QString ConstantGUI::LINE_EDIT_IS_EDITTING = QString("\
  QLineEdit {\
      border: 0px;\
      border-radius: 3px;\
      background-color: rgb(240, 240, 240);\
  }\
");

const QString ConstantGUI::VERTICAL_SCROLL_STYLE_TESTING = QString("\
     QScrollArea {\
         border: .3 px;\
         border-radius: 8px;\
         background-color: rgb(230, 230, 230);\
     }\
");;
