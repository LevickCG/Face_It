#ifndef PSW_MODF_H
#define PSW_MODF_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class psw_modf;
}

class psw_modf : public QWidget
{
    Q_OBJECT

public:
    explicit psw_modf(QWidget *parent = nullptr);
    ~psw_modf();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_yes_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::psw_modf *ui;
};

#endif // PSW_MODF_H
