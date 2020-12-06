#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>

#include <QCamera>              //use the camera and get still image
#include <QCameraImageCapture>
#include <QImage>
#include <QCameraViewfinder>

#include <QFileDialog>//load file

#include <QtNetwork>//netwokr library
#include <QByteArray>

#include <QJsonObject>//lribraries for compose and analyse Json format data
#include <QJsonArray>
#include <QJsonDocument>
#include "global_var.h"
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class camera;
}

class camera : public QWidget
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = nullptr);
    ~camera();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::camera *ui;
    QCamera *the_camera;//camera
    QCameraViewfinder * viewfinder;//rendering viewer
    QCameraImageCapture * imageCapture;//image capturer

};

#endif // CAMERA_H
