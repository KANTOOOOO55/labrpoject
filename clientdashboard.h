#ifndef CLIENTDASHBOARD_H
#define CLIENTDASHBOARD_H

#include <QDialog>

namespace Ui {
class ClientDashboard;
}

class ClientDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDashboard(QWidget *parent = nullptr, QString clientName = "");
    ~ClientDashboard();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonSave_clicked();

    int calculateDaysBetween(const QString& date1, const QString& date2);
    void on_pushButtonSave_2_clicked();

    QString checkIfDateIsAvailable(QString itemName, QString fromDate, QString toDate);
private:
    Ui::ClientDashboard *ui;
};

#endif // CLIENTDASHBOARD_H
