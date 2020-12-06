#ifndef SQL_LOG_H
#define SQL_LOG_H

#include <QWidget>
#include <QtSql>
#include <QSqlTableModel>
#include <QSqlDatabase>


namespace Ui {
class sql_log;
}

class sql_log : public QWidget
{
    Q_OBJECT

public:
    explicit sql_log(QWidget *parent = nullptr);
    ~sql_log();

private:
    Ui::sql_log *ui;
};

#endif // SQL_LOG_H
