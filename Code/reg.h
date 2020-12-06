#ifndef REG_H
#define REG_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql>
#include <QImage>
#include <QFileDialog>

#include <QtNetwork>//netwokr library

#include <QByteArray>//used in image conversion

#include <QJsonObject>//lribraries for compose and analyse Json format data
#include <QJsonArray>
#include <QJsonDocument>

#include "global_var.h"//to use the previously defined variables, like url

namespace Ui {
class reg;
}

class reg : public QWidget
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent = nullptr);
    ~reg();

private slots:
    void on_psbut_no_clicked();

    void on_psbut_yes_clicked();

    void on_pushButton_clicked();

private:
    Ui::reg *ui;
    QImage *img_to_upload;
};

#endif // REG_H
