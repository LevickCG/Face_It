#include "user_win.h"
#include "ui_user_win.h"

user_win::user_win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_win)
{
    ui->setupUi(this);
}

user_win::~user_win()
{
    delete ui;
}

void user_win::on_pushButton_clicked()
{
    camera_win=new camera();
    camera_win->show();
}

void user_win::on_pushButton_4_clicked()
{
    this->close();
}

void user_win::on_pushButton_3_clicked()
{
    psw_modf_win=new psw_modf();
    psw_modf_win->show();
}

void user_win::on_pushButton_2_clicked()
{
    face_revew_win=new face_renew();
    face_revew_win->show();
}
