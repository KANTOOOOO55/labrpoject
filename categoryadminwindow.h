#ifndef CATEGORYADMINWINDOW_H
#define CATEGORYADMINWINDOW_H

#include <QDialog>

namespace Ui {
class CategoryAdminWindow;
}

class CategoryAdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryAdminWindow(QWidget *parent = nullptr);
    ~CategoryAdminWindow();

private slots:

    void on_pushButtonAddNewCategory_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonReturn_clicked();

private:
    Ui::CategoryAdminWindow *ui;
};

#endif // CATEGORYADMINWINDOW_H
