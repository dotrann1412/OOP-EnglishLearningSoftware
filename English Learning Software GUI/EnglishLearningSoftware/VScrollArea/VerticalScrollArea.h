#ifndef VERTICALSCROLLAREA_H
#define VERTICALSCROLLAREA_H

#include <QScrollArea>
#include <QGridLayout>
#include <QScrollArea>
#include <QScrollBar>

#include <Constant/ConstantGUI.h>


class VerticalScrollArea : public QScrollArea
{
private:
    QWidget* contentWidget;
    QGridLayout* grid;
    int nCols; // columns of each row;
    int count; // the number of widget

public:
    VerticalScrollArea(int cols, QWidget* parent = Q_NULLPTR);
    ~VerticalScrollArea();

public:
    void addWidget(QWidget*);
};

#endif // VERTICALSCROLLAREA_H
