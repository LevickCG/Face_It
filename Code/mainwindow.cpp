#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->pushButton_reg,SIGNAL(clicked()),this,SLOT(on_pushButton_reg_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_log_clicked(bool checked)
{
    if(ui->lineEdit_main_account->text().trimmed().isEmpty()||ui->lineEdit_main_psw->text().trimmed().isEmpty())
    {
        QMessageBox::information(this,"登陆失败","用户名或密码不能为空!");
    }
    else
    {
        if(ui->lineEdit_main_psw->text().length()<6||ui->lineEdit_main_psw->text().length()>20||ui->lineEdit_main_account->text().length()<6||ui->lineEdit_main_account->text().length()>20)
        {
            QMessageBox::information(this,"登陆失败","密码长度非法!");
        }
        else
        {
            if(ui->lineEdit_main_psw->text().contains(QRegExp("[\\x4e00-\\x9fa5]+"))||ui->lineEdit_main_account->text().contains(QRegExp("[\\x4e00-\\x9fa5]+")))
            {
                //Chinese is detected in ID or password
                QMessageBox::information(this,"登陆失败","用户名或密码不能含有中文!");
            }
            else
            {
                QString u_id=ui->lineEdit_main_account->text();
                QString u_psw=ui->lineEdit_main_psw->text();
                //connect to the database and now log in
                /*QMessageBox log_success;
                log_success.setText("登陆成功!欢迎你");
                log_success.setStandardButtons("确认");*/
                QString if_in=QString("select * from identity where id='%1' and psw='%2'").arg(u_id).arg(u_psw);// return the result of query
                QSqlQuery query;
                query.exec(if_in);
                if(query.first()){
                    QMessageBox::information(this, "登陆成功", "登陆成功,欢迎使用!");
                    QString identity =query.value("identity_name").toString();
                    if(identity=="admin"){
                        admin_window=new admin_win();
                        admin_window->show();                        
                    }
                    else{
                        user_window=new user_win();
                        user_window->show();                        
                    }
                }
                else{
                    QMessageBox::information(this,"登陆失败","用户名或密码错误，请重试!");
                }
            }
        }
    }
}

void MainWindow::on_pushButton_reg_clicked()
{
    reg_win=new reg;
    reg_win->show();
}

void MainWindow::on_pushButton_out_clicked()
{
    this->close();
}
