#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class infoDialog;
}

class infoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit infoDialog(QWidget *parent = 0);
    ~infoDialog();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::infoDialog *ui;
};

#endif // INFODIALOG_H
