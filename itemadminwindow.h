#ifndef ITEMADMINWINDOW_H
#define ITEMADMINWINDOW_H

#include <QDialog>

namespace Ui {
class ItemAdminWindow;
}

class ItemAdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ItemAdminWindow(QWidget *parent = nullptr);
    ~ItemAdminWindow();

private slots:
    void on_pushButtonAddNewItem_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonReturn_clicked();

private:
    Ui::ItemAdminWindow *ui;
};

#endif // ITEMADMINWINDOW_H
