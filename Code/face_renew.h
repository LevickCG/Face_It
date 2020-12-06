#ifndef FACE_RENEW_H
#define FACE_RENEW_H

#include <QWidget>
#include <QImage>
#include <QtSql>
#include <QMessageBox>
#include <QFileDialog>//load file

#include <QtNetwork>//netwokr library

#include <QByteArray>//used in image conversion

#include <QJsonObject>//lribraries for compose and analyse Json format data
#include <QJsonArray>
#include <QJsonDocument>
#include "global_var.h"

namespace Ui {
class face_renew;
}

class face_renew : public QWidget
{
    Q_OBJECT

public:
    explicit face_renew(QWidget *parent = nullptr);
    ~face_renew();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::face_renew *ui;
    QImage *img_to_renew;
};

#endif // FACE_RENEW_H
