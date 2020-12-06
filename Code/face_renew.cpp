#include "face_renew.h"
#include "ui_face_renew.h"

face_renew::face_renew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::face_renew)
{
    ui->setupUi(this);
}

face_renew::~face_renew()
{
    delete ui;
}

void face_renew::on_pushButton_3_clicked()
{

    QString file_path=QFileDialog::getOpenFileName(this,"选择用户图片","C:/Users/Levick/Desktop","Images(*.png *.jpg *jpeg *bmp)");
    img_to_renew= new QImage();
    img_to_renew->load(file_path);
    ui->label_img_display->setScaledContents(true);
    ui->label_img_display->setPixmap(QPixmap::fromImage(*img_to_renew));

}

void face_renew::on_pushButton_clicked()
{
    QString face_token;//we declare face_token previously, we shall use it later
    QString user_info;

    QString user_id=ui->lineEdit_account->text();
    QString if_user_exist=QString("select * from identity where id='%1';").arg(user_id);
    QSqlQuery query;
    if(query.exec(if_user_exist)&&query.first()){
        user_info=query.value("user_name").toString();

        //first we need to convert the image from jpg to base64 format        
        QByteArray bytes;
        QBuffer buffer(&bytes);
        img_to_renew->save(&buffer,"jpg");

        QString base64str = QString(bytes.toBase64());
        buffer.close();
        //convertion complete

        //Now we build the request in json format

        QJsonObject reg_json;
        reg_json.insert("image",base64str);
        reg_json.insert("image_type","BASE64");
        reg_json.insert("group_id","demo");//demo is the id of my face group, can be diffrent
        reg_json.insert("user_id",user_id);
         reg_json.insert("user_info",user_info);
        reg_json.insert("quality_control","NONE");// we don't control the image quality here for simplicity
        reg_json.insert("liveness_control","NONE");//we don't control the liveness here for simplicity
        reg_json.insert("action_type","UPDATE");//we replace the image
        //reg_json composition complete

        //Now we begin the http post
        QJsonDocument reg_json_doc;
        QByteArray reg_data;
        QNetworkRequest reg_request;
        QNetworkReply *reg_reply;
        QNetworkAccessManager *http_manager=new QNetworkAccessManager(this);

        reg_json_doc.setObject(reg_json);
        reg_data=reg_json_doc.toJson(QJsonDocument::Compact);
        QUrl reg_url(user_update);//url initiation

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
            qDebug()<<"error code::"+error_code;
            if(error_code==""){
                QJsonObject result=root_obj.value("result").toObject();

                face_token=result.value("face_token").toString();//that all we need from the reply
                qDebug()<<"FaceToken::"+face_token;

                QString ins= QString("update identity set face_token='%1' where id='%2';").arg(face_token).arg(user_id);

                QSqlQuery query_for_renew;
                if(query_for_renew.exec(ins)){
                    QMessageBox::information(this, "成功", "更新成功!");
                    this->close();
                }
                else{
                    QMessageBox::information(this,"更新失败","更新失败,请重试!");

                }
            }
            else{
                QMessageBox::information(this,"更新失败","请求发生错误,请重试!");
            }

         }

    }
    else{
        QMessageBox::information(this,"Error","用户不存在,请确认后重试!");
    }
}

void face_renew::on_pushButton_2_clicked()
{
    this->close();
}
