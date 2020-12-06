#ifndef ADMIN_WIN_H
#define ADMIN_WIN_H

#include <QWidget>
#include "camera.h"
#include "global_var.h"
#include "reg.h"
#include "user_delete.h"
#include "face_renew.h"
#include "sql_log.h"

namespace Ui {
class admin_win;
}

class admin_win : public QWidget
{
    Q_OBJECT

public:
    explicit admin_win(QWidget *parent = nullptr);
    ~admin_win();

private slots:
    void on_psbut_face_rec_clicked();

    void on_psbut_back_clicked();

    void on_psbut_adduser_clicked();

    void on_psbut_deluser_clicked();

    void on_psbut_modf_user_clicked();

    void on_psbut_modf_user_2_clicked();

private:
    Ui::admin_win *ui;
    camera *camera_win;
    reg *reg_win;
    user_delete *user_delete_win;
    face_renew *face_renew_win;
    sql_log *sql_log_win;
};

#endif // ADMIN_WIN_H
