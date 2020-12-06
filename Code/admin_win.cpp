#include "admin_win.h"
#include "ui_admin_win.h"

admin_win::admin_win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_win)
{
    ui->setupUi(this);
}

admin_win::~admin_win()
{
    delete ui;
    delete camera_win;
}

void admin_win::on_psbut_face_rec_clicked()
{
    camera_win=new camera();
    camera_win->show();
}

void admin_win::on_psbut_back_clicked()
{
    this->close();
}

void admin_win::on_psbut_adduser_clicked()
{
    reg_win  =new reg();
    reg_win->show();
}

void admin_win::on_psbut_deluser_clicked()
{
    user_delete_win=new user_delete();
    user_delete_win->show();
}

void admin_win::on_psbut_modf_user_clicked()
{
    face_renew_win=new face_renew();
    face_renew_win->show();
}

void admin_win::on_psbut_modf_user_2_clicked()
{
    sql_log_win=new sql_log();
    sql_log_win->show();
}
