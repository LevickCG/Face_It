#include "reg.h"
#include "ui_reg.h"
reg::reg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);
}

reg::~reg()
{
    delete ui;
}

void reg::on_psbut_no_clicked()
{
    this->close();
}

void reg::on_psbut_yes_clicked()
{
    QString face_token;//we declare face_token previously, we shall use it later

    if(ui->lnedt_reg_act->text().trimmed().length()==0||ui->lnedt_reg_psw->text().trimmed().length()==0||ui->lnedt_reg_psw2->text().trimmed().length()==0){
        QMessageBox::information(this,"注册失败","账号或密码不能为空!");
    }
    else{
        if(ui->lnedt_reg_act->text().trimmed().length()<6||ui->lnedt_reg_psw->text().trimmed().length()<6||ui->lnedt_reg_psw2->text().trimmed().length()<6||ui->lnedt_reg_act->text().trimmed().length()>20||ui->lnedt_reg_psw->text().trimmed().length()>20||ui->lnedt_reg_psw2->text().trimmed().length()>20){
            QMessageBox::information(this,"注册失败","账号或密码长度非法!");
        }
        else{// apply RegExp to detect Chinese character
            if(ui->lnedt_reg_act->text().contains(QRegExp("[\\x4e00-\\x9fa5]+"))||ui->lnedt_reg_psw2->text().contains(QRegExp("[\\x4e00-\\x9fa5]+"))||ui->lnedt_reg_psw->text().contains(QRegExp("[\\x4e00-\\x9fa5]+"))){
                QMessageBox::information(this, "注册失败", "账号或密码不能含有中文!");
            }
            else{
                if(ui->lnedt_reg_psw->text()!=ui->lnedt_reg_psw2->text()){
                    QMessageBox::information(this, "注册失败", "两次密码输入不一致!");
                }
                else{

                    //Now we begin to use baidu api "user_add" "via https://aip.baidubce.com/rest/2.0/face/v3/faceset/user/add"

                    //first we need to convert the image from jpg to base64 format
                    QByteArray bytes;
                    QBuffer buffer(&bytes);
                    img_to_upload->save(&buffer,"jpg");

                    QString base64str = QString(bytes.toBase64());
                    buffer.close();
                    //convertion complete

                    //Now we build the request in json format

                    QJsonObject reg_json;
                    reg_json.insert("image",base64str);
                    reg_json.insert("image_type","BASE64");
                    reg_json.insert("group_id","demo");//demo is the id of my face group, can be diffrent
                    reg_json.insert("user_id",ui->lnedt_reg_act->text());
                    reg_json.insert("user_info",ui->lnedt_reg_name->text());
                    reg_json.insert("quality_control","NONE");// we don't control the image quality here for simplicity
                    reg_json.insert("liveness_control","NONE");//we don't control the liveness here for simplicity
                    reg_json.insert("action_type","APPEND");//we append the image ,not replace
                    //reg_json composition complete

                    //Now we begin the http post
                    QJsonDocument reg_json_doc;
                    QByteArray reg_data;
                    QNetworkRequest reg_request;
                    QNetworkReply *reg_reply;
                    QNetworkAccessManager *http_manager=new QNetworkAccessManager(this);

                    reg_json_doc.setObject(reg_json);
                    reg_data=reg_json_doc.toJson(QJsonDocument::Compact);
                    QUrl reg_url(user_add);//url initiation

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

                    //now the reply should be available, we now analyse the reply
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

                            QString ins= QString("insert into identity values('%1','%2','%3','%4','user');").arg(ui->lnedt_reg_act->text()).arg(ui->lnedt_reg_name->text()).arg(ui->lnedt_reg_psw->text()).arg(face_token);
                            QString if_name_dul=QString("select * from identity where id='%1';").arg(ui->lnedt_reg_act->text());
                            QSqlQuery query;
                            if(query.exec(ins)){//register success
                                QMessageBox::information(this, "成功", "注册成功!");
                                this->close();
                            }
                            else if(query.exec(if_name_dul)&&query.first()){
                                QMessageBox::information(this, "注册失败", "此id已被占用!");
                            }
                            else{
                                QMessageBox::information(this,"注册失败","注册失败,请重试!");

                            }
                        }
                        else{
                            QMessageBox::information(this,"注册失败","请求发生错误,请重试!");
                        }



                        /*
                        if(jsonError_reg.error!=QJsonParseError::NoError){//if json error
                            qDebug()<<"JSON format error";
                        }
                        else{//json format is right, analyse begins

                        }
                        */
                    }
                    else{
                        QMessageBox::information(this,"错误","请求错误,请重试!");
                    }
                }
            }
        }
    }
}

void reg::on_pushButton_clicked()//choose the image of user and display it
{
    QString file_path=QFileDialog::getOpenFileName(this,"选择用户图片","C:/Users/Levick/Desktop","Images(*.png *.jpg *jpeg *bmp)");
    img_to_upload= new QImage;
    img_to_upload->load(file_path);
    ui->img_display->setScaledContents(true);
    ui->img_display->setPixmap(QPixmap::fromImage(*img_to_upload));
}
