#ifndef ACCOUNTSADMINWINDOW_H
#define ACCOUNTSADMINWINDOW_H

#include <QDialog>

namespace Ui {
class AccountsAdminWindow;
}

class AccountsAdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AccountsAdminWindow(QWidget *parent = nullptr);
    ~AccountsAdminWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::AccountsAdminWindow *ui;
};

#endif // ACCOUNTSADMINWINDOW_H
