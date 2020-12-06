#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "reg.h"
#include "admin_win.h"
#include "user_win.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_log_clicked(bool checked);

    void on_pushButton_reg_clicked();

    void on_pushButton_out_clicked();

private:
    Ui::MainWindow *ui;
    reg *reg_win;
    admin_win *admin_window;
    user_win *user_window;
};
#endif // MAINWINDOW_H
