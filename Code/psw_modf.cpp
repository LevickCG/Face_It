#include "psw_modf.h"
#include "ui_psw_modf.h"

psw_modf::psw_modf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::psw_modf)
{
    ui->setupUi(this);
}

psw_modf::~psw_modf()
{
    delete ui;
}

void psw_modf::on_pushButton_2_clicked()
{
    this->close();
}

void psw_modf::on_pushButton_yes_clicked()
{
    if(ui->lineEdit_account->text().trimmed().length()==0||ui->lineEdit_pre_psw->text().trimmed().length()==0||ui->lineEdit_new_psw->text().trimmed().length()==0){
        QMessageBox::information(this,"","用户名或密码不能为空!");
    }
    else{
        if(ui->lineEdit_account->text().trimmed().length()<6||ui->lineEdit_new_psw->text().trimmed().length()<6||ui->lineEdit_pre_psw->text().trimmed().length()<6||ui->lineEdit_account->text().trimmed().length()>20||ui->lineEdit_new_psw->text().trimmed().length()>20||ui->lineEdit_pre_psw->text().trimmed().length()>20){
            QMessageBox::information(this,"","用户名或密码长度非法");
        }
        else{
            if(ui->lineEdit_account->text().trimmed().contains(QRegExp("[\\x4e00-\\x9fa5]+"))||ui->lineEdit_new_psw->text().contains(QRegExp("[\\x4e00-\\x9fa5]+"))||ui->lineEdit_pre_psw->text().trimmed().contains(QRegExp("[\\x4e00-\\x9fa5]+"))){
                QMessageBox::information(this,"","用户名或密码不能含有中文字符");
            }
            else{
                QString get_psw=QString("select psw from identity where id='%1'").arg(ui->lineEdit_account->text());
                QString pre_psw;
                QSqlQuery query;
                if(query.exec(get_psw)){//
                    query.first();
                    pre_psw=query.value("psw").toString();
                    if(pre_psw==ui->lineEdit_pre_psw->text()){
                        QString update_query=QString("update identity set psw='%1' where id='%2'").arg(ui->lineEdit_new_psw->text()).arg(ui->lineEdit_account->text());
                        if(query.exec(update_query)){
                            QMessageBox::information(this,"","修改密码成功!");
                            this->close();
                        }
                        else{
                            QMessageBox::information(this,"","数据库更新失败!");
                        }

                    }
                    else{
                        QMessageBox::information(this,"","原密码错误,请确认后重试!");
                    }

                }
                else{
                    QMessageBox::information(this,"","此用户不存在!");
                }
            }
        }
    }


}

void psw_modf::on_pushButton_back_clicked()
{
    this->close();
}
