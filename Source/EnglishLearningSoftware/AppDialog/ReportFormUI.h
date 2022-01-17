#ifndef REPORTFORMUI_H
#define REPORTFORMUI_H

#include <QWidget>

namespace Ui {
class ReportFormUI;
}

class ReportFormUI : public QWidget
{
    Q_OBJECT

public:
    explicit ReportFormUI(QWidget *parent = nullptr);
    ~ReportFormUI();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ReportFormUI *ui;
};

#endif // REPORTFORMUI_H
