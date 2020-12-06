#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("47.94.xx.xxx");//host name of your database server, localhost if running MySql in local PC
    db.setDatabaseName("Name_of_your_database");
    db.setUserName("Usr_name");
    db.setPort(3306);
    db.setPassword("Your_password");
    if(!db.open()){
        QMessageBox::warning(NULL,"运行错误","数据库连接失败！");
    }
    else{
        w.show();
    }
    return a.exec();
}
