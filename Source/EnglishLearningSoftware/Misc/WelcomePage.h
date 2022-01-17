#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>

namespace Ui {
class WelcomePage;
}

class WelcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();

private slots:
    void on_label_2_linkActivated(const QString &link);

private:
    Ui::WelcomePage *ui;
};

#endif // WELCOMEPAGE_H
