#ifndef USER_WIN_H
#define USER_WIN_H

#include <QWidget>
#include "camera.h"
#include "global_var.h"
#include "psw_modf.h"
#include "face_renew.h"


namespace Ui {
class user_win;
}

class user_win : public QWidget
{
    Q_OBJECT

public:
    explicit user_win(QWidget *parent = nullptr);
    ~user_win();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::user_win *ui;
    camera *camera_win;
    psw_modf *psw_modf_win;
    face_renew *face_revew_win;
};

#endif // USER_WIN_H
