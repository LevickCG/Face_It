#include "camera.h"
#include "ui_camera.h"

camera::camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
    the_camera=new QCamera;
    viewfinder=new QCameraViewfinder(this);
    imageCapture=new QCameraImageCapture(the_camera);

    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);//set where to store the image
    the_camera->setCaptureMode(QCamera::CaptureStillImage);//set the mode, we store still image, not taping
    the_camera->setViewfinder(viewfinder);//set the rendering object

    the_camera->start(); //boot the camera
}

camera::~camera()
{
    delete ui;
}

void camera::on_pushButton_clicked()
{
    the_camera->searchAndLock();//lock the camera
    imageCapture->capture("C:/Users/Levick/Pictures/FaceIt_img/img_used_for_recognition.jpg");//save the image to the disk with fixed file name
    the_camera->unlock();//unlock the camera
    QImage *face_img=new QImage;
    face_img->load("C:/Users/Levick/Pictures/FaceIt_img/img_used_for_recognition.jpg");
    ui->label_img_show->setScaledContents(true);//make the img show in the size of the label.
    ui->label_img_show->setPixmap(QPixmap::fromImage(*face_img));

    //first we need to convert the image from jpg to base64 format
    QByteArray bytes;
    QBuffer buffer(&bytes);
    face_img->save(&buffer,"jpg");

    QString base64str = QString(bytes.toBase64());
    buffer.close();
    //convertion complete

    //Now we build the request in json format

    QJsonObject search_json;
    search_json.insert("image",base64str);
    search_json.insert("image_type","BASE64");
    search_json.insert("group_id_list","demo");//demo is the id of my face group, can be diffrent
    search_json.insert("quality_control","NONE");// we don't control the image quality here for simplicity
    search_json.insert("liveness_control","NONE");//we don't control the liveness here for simplicity
    //search_json composition complete

    //Now we begin the http post
    QJsonDocument face_search_json_doc;
    QByteArray face_search_data;
    QNetworkRequest search_request;
    QNetworkReply *search_reply;
    QNetworkAccessManager *http_manager=new QNetworkAccessManager(this);

    face_search_json_doc.setObject(search_json);
    face_search_data=face_search_json_doc.toJson(QJsonDocument::Compact);
    QUrl face_search_url(search);//url initiation

    search_request.setUrl(face_search_url);
    search_request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    search_reply=http_manager->post(search_request,face_search_data);
    //search_request composition complete

    //we set a timer to ensure we get a reply before we continue
    QEventLoop _loop;
    QTimer _timer;
    connect(search_reply,SIGNAL(finished()),&_loop,SLOT(quit()));
    connect(&_timer,SIGNAL(timerout()),&_loop,SLOT(quit()));
    _timer.start(2000);// 1000 ms
    _loop.exec();

    if(!_timer.isActive()){
        QMessageBox::information(this,"超时","请求超时,请重试!");
    }
    _timer.deleteLater();
    _loop.deleteLater();

    //now the reply should be available, we now analyse the reply

    if(search_reply->error()==QNetworkReply::NoError){
        QByteArray bytes_rep= search_reply->readAll();


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
            QJsonValue user_list=result.value("user_list");
            QJsonObject list_info=user_list.toArray().at(0).toObject();
            QString user_info=list_info.value("user_info").toString();
            ui->label_result_show->setText(user_info);


               /*
            QString find_info=QString("select user_name from identity where face_token='%1';").arg(face_token);
            QSqlQuery query;
            if(query.exec(find_info)){//register success
                query.first();
                QString user_name=query.value("user_name").toString();
                ui->label_result_show->setText(user_name);

            }
            else{
                ui->label_result_show->setText("No match!");
            }
            */
        }
        else{
            ui->label_result_show->setText("请求失败,请重试！");
        }
    }
    else{
        QMessageBox::information(this,"错误","请求错误,请重试!");
    }
}

void camera::on_pushButton_back_clicked()
{
    the_camera->stop();
    this->close();
}
