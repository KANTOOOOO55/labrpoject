#ifndef CLIENTRENTALHISTORY_H
#define CLIENTRENTALHISTORY_H

#include <QDialog>

namespace Ui {
class ClientRentalHistory;
}

class ClientRentalHistory : public QDialog
{
    Q_OBJECT

public:
    explicit ClientRentalHistory(QWidget *parent = nullptr, QString clientName = "", bool isAdmin = false);
    ~ClientRentalHistory();

private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::ClientRentalHistory *ui;
};

#endif // CLIENTRENTALHISTORY_H
