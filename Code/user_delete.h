#ifndef USER_DELETE_H
#define USER_DELETE_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql>
#include "global_var.h"

#include <QtNetwork>//netwokr library

#include <QByteArray>//used in image conversion

#include <QJsonObject>//lribraries for compose and analyse Json format data
#include <QJsonArray>
#include <QJsonDocument>

namespace Ui {
class user_delete;
}

class user_delete : public QWidget
{
    Q_OBJECT

public:
    explicit user_delete(QWidget *parent = nullptr);
    ~user_delete();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::user_delete *ui;
};

#endif // USER_DELETE_H
