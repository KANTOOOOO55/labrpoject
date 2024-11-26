#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QDialog>

namespace Ui {
class AdminDashBoard;
}

class AdminDashBoard : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDashBoard(QWidget *parent = nullptr);
    ~AdminDashBoard();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AdminDashBoard *ui;
};

#endif // ADMINDASHBOARD_H
