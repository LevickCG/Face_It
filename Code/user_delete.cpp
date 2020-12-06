#include "user_delete.h"
#include "ui_user_delete.h"

user_delete::user_delete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_delete)
{
    ui->setupUi(this);
}

user_delete::~user_delete()
{
    delete ui;
}

void user_delete::on_pushButton_2_clicked()
{
    this->close();
}

void user_delete::on_pushButton_clicked()
{
    QString user_id=ui->lineEdit_account->text();
    QString face_token;

    QString get_face_token=QString("select face_token from identity where id='%1'").arg(user_id);
    QSqlQuery query;
    if(query.exec(get_face_token)&&query.first()){
        qDebug()<<query.exec(get_face_token);
        qDebug()<<query.first();

        //Now we build the request in json format
        face_token=query.value("face_token").toString();

        QJsonObject reg_json;
        reg_json.insert("user_id",user_id);
        reg_json.insert("group_id","demo");//demo is the id of my face group, can be diffrent
        reg_json.insert("face_token",face_token);

        //reg_json composition complete

        //Now we begin the http post
        QJsonDocument reg_json_doc;
        QByteArray reg_data;
        QNetworkRequest reg_request;
        QNetworkReply *reg_reply;
        QNetworkAccessManager *http_manager=new QNetworkAccessManager(this);

        reg_json_doc.setObject(reg_json);
        reg_data=reg_json_doc.toJson(QJsonDocument::Compact);
        QUrl reg_url(face_delete);//url initiation

        reg_request.setUrl(reg_url);
        reg_request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
        reg_reply=http_manager->post(reg_request,reg_data);
        //reg_request composition complete

        //we set a timer to ensure we get a reply before we continue
        QEventLoop _loop;
        QTimer _timer;
        connect(reg_reply,SIGNAL(finished()),&_loop,SLOT(quit()));
        connect(&_timer,SIGNAL(timerout()),&_loop,SLOT(quit()));
        _timer.start(2000);// 1000 ms
        _loop.exec();

        if(!_timer.isActive()){
            QMessageBox::information(this,"超时","请求超时,请重试!");
        }
        _timer.deleteLater();
        _loop.deleteLater();

        if(reg_reply->error()==QNetworkReply::NoError){
            QByteArray bytes_rep= reg_reply->readAll();
            //QJsonParseError jsonError_reg;

            //convert to json


            QString str_json=bytes_rep;
         //   QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError_reg);// not work, ended up empty
        //    str_json.replace("\\\\","\\");
        //    str_json.replace("\\\"","\"");


            QJsonDocument document=QJsonDocument::fromJson(str_json.toUtf8().data());

            qDebug()<<str_json;

            QJsonObject root_obj=document.object();
            QString error_code=root_obj.value("error_code").toString();//get the error_code, right results if error_code=0

            if(error_code==""){
                QMessageBox::information(this,"成功","删除账号成功!");
            }
        }
        else{
            qDebug()<<"reply error";
        }

    }
    else{
        if(query.exec(get_face_token) && !query.first()){
            QMessageBox::information(this,"错误","账号不存在,请确认后重试");
        }
        else{
            QMessageBox::information(this,"错误","数据库语句执行错误!");
        }
    }


}
