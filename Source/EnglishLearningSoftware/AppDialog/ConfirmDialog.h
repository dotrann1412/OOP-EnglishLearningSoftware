#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

class ConfirmDialog : public QDialog
{
public:
    ConfirmDialog(QString message);
    ~ConfirmDialog();
};

#endif // CONFIRMDIALOG_H
