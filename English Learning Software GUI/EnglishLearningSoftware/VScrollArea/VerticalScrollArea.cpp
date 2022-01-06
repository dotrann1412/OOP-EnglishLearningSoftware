#include "VerticalScrollArea.h"

#include <Constant/ConstantGUI.h>
#include <QSizePolicy>

VerticalScrollArea::VerticalScrollArea(int cols, QWidget* parent)
    : QScrollArea(parent),
      nCols(cols) {

    this->setWidgetResizable(true);
    contentWidget = new QWidget(this);
    this->setWidget(contentWidget);
    contentWidget->setLayoutDirection(Qt::LeftToRight);

    grid = new QGridLayout(contentWidget);

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setStyleSheet(ConstantGUI::VERTICAL_SCROLL_STYLE);

    this->count = 0;
}

VerticalScrollArea::~VerticalScrollArea(){
    delete this->grid;
    delete this->contentWidget;
}

void VerticalScrollArea::addWidget(QWidget *w) {
    if(!w)
        return;

    int row = count / nCols;
    int col = count % nCols;
    this->grid->addWidget(w, row, col);

    if(!(count % nCols)) {
        int height = w->height() * ((count + nCols - 1) / nCols + 1);
        this->contentWidget->setFixedHeight(height + ConstantGUI::QUESTION_BUTTON_PADDING * ((count + nCols - 1) / nCols + 1));
    }

    this->count++;
}
