#ifndef RENTALREQUESTSADMINWINDOW_H
#define RENTALREQUESTSADMINWINDOW_H

#include <QDialog>

namespace Ui {
class RentalRequestsAdminWindow;
}

class RentalRequestsAdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RentalRequestsAdminWindow(QWidget *parent = nullptr);
    ~RentalRequestsAdminWindow();

private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::RentalRequestsAdminWindow *ui;
};

#endif // RENTALREQUESTSADMINWINDOW_H
