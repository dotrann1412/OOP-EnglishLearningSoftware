#include "ConstantGUI.h"

const QString ConstantGUI::VERTICAL_SCROLL_STYLE = QString("\
       QScrollArea {\
           border: none;\
       }\
       QScrollBar {\
           background: rgb(128, 128, 128);\
       }\
       QScrollBar:vertical {\
           width: 0px;\
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

const QString ConstantGUI::VERTICAL_SCROLL_STYLE_S = QString("\
       QScrollArea {\
           border: none;\
       }\
       QScrollBar {\
           background: rgb(128, 128, 128);\
       }\
       QScrollBar:vertical {\
           width: 10px;\
           border-radius: 5px;\
       }\
       QScrollBar::handle {\
           width: 10px;\
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
    QWidget {"
             "border: 1px solid black; border-radius: 10px;\
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
     background-color: rgb(230, 230, 230);\
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
    border: .5px solid rgb(55, 45, 135);\
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
 QLineEdit {\
     border: 0px;\
     border-radius: 3px;\
     background-color: rgb(240, 240, 240);\
 }\
");

const QString ConstantGUI::PUSH_BUTTON_REGISTERED = QString("\
QLineEdit {\
   border: 0px;\
   border-radius: 3px;\
   background-color: rgb(240, 240, 240);\
}\
");

const QString ConstantGUI::QUESTION_STATEMENT_STYLE_2 = QString("QLabel {\
    color: #000; \
    background-color: #fff; \
    font-size: 15px;\
    font-weight: bold;\
    border-top: 3px;\
}");

const QString ConstantGUI::QUESTION_STATEMENT_STYLE_1 = QString("\
QLabel {\
   color: #000; \
   background-color: rgb(240, 240, 240); \
   font-size: 15px;\
   font-weight: bold;\
}");

const QString ConstantGUI::QUESTION_STATEMENT_STYLE_3 = QString("\
QLabel {\
   color: #000; \
   background-color: rgb(240, 240, 240); \
   font-size: 15px;\
   font-weight: bold;\
}");

const QString ConstantGUI::QUESTION_ANS_BUTTON_HOVER_STYLE = QString("\
    QPushButton {\
        background-color: rgb(230, 230, 230);\
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
        border: .5px solid rgb(55, 45, 135);\
    }\
        QPushButton:hover {\
    }"
);

const QString ConstantGUI::QUESTION_ANS_BUTTON_CLICKED = QString("\
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
}");

const QString ConstantGUI::QUESTION_CORRECT_ANS = QString("\
    QPushButton {\
        background-color: rgb(11, 125, 42);\
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
}");

const QString ConstantGUI::QUESTION_CORRECT_ANS_S = QString("\
  QPushButton {\
      background-color: rgb(11, 125, 20);\
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
}");

const QString ConstantGUI::QUESTION_CORRECT_ANS_HOVER = QString("\
  QPushButton {\
      background-color: rgb(11, 125, 42);\
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
QPushButton:hover:!pressed\
{\
    border: .3px solid rgb(55, 45, 135);\
}\
    QPushButton:hover {\
    background-color: rgb(8, 70, 20);\
}\
}");

const QString ConstantGUI::QUESTION_WRONG_ANS_HOVER = QString("\
    QPushButton {\
       background-color: rgb(148, 10, 26);\
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
QPushButton:hover:!pressed\
{\
  border: .3px solid rgb(55, 45, 135);\
}\
  QPushButton:hover {\
  background-color: rgb(120, 7, 10);\
}\
}");

const QString ConstantGUI::QUESTION_ANS_BUTTON_HIDEN_ANS = QString("\
    QPushButton {\
            background-color: rgba(230, 230, 230, 60);\
            border-radius: 12px; \
            color: rgba(50, 50, 50, 60);\
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
"
);

const QString ConstantGUI::QUESTION_WRONG_ANS = QString("\
    QPushButton {\
       background-color: rgb(148, 10, 26);\
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
}");

const QString ConstantGUI::BLANK_QUESTION_WRONG_ANS = QString("\
QLineEdit {\
    background-color: rgba(148, 10, 26, 50);\
    border-radius: 12px;  color: rgb(0, 0, 0);\
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
    margin-left: 15px\
}");

const QString ConstantGUI::BLANK_QUESTION_CORRECT_ANS = QString("\
QLineEdit {\
    background-color: rgba(11, 135, 42, 50);\
    border-radius: 12px;  color: rgb(0, 0, 0);\
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
    margin-left: 15px\
}");


const QString ConstantGUI::BLANK_QUESTION_STYLE = QString("\
QLineEdit {\
    background-color: rgba(240, 240, 240, 255);\
    border-radius: 12px;  color: rgb(0, 0, 0);\
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
    margin-left: 15px\
}");

const QString ConstantGUI::DIALOG_MESSAGE_STYLE = QString("\
     color: #000; \
     background-color: rgba(0, 0, 0, 0); \
     font-size: 15px;\
     font-weight: bold;\
");

const QString ConstantGUI::CONFIRM_DIALOG_BUTTON_ACCEPTED = QString("\
QPushButton {\
    background-color: rgb(220, 220, 220);\
    border-radius: 12px; \
    color: rgb(46, 45, 41); \
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
    border: .3px solid rgb(55, 45, 135);\
}\
    QPushButton:hover {\
    background-color: rgb(170, 170, 170);\
}\
");

const QString ConstantGUI::CONFIRM_DIALOG_BUTTON_REJECTED = QString("\
QPushButton {\
  background-color: rgb(220, 220, 220);\
  border-radius: 12px; \
  color: rgb(46, 45, 41); \
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
  border: .3px solid rgb(55, 45, 135);\
}\
  QPushButton:hover {\
  background-color: rgb(170, 170, 170);\
}\
");
