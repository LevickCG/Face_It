#include "sql_log.h"
#include "ui_sql_log.h"

sql_log::sql_log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sql_log)
{
    ui->setupUi(this);
    /*
    QSqlTableModel * model = new QSqlTableModel(this,db);
    model->setTable("log");
    ui->tableview().select(model);
    model->select();
    */
}

sql_log::~sql_log()
{
    delete ui;
}
