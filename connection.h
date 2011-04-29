#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtGui>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}

static bool createDefaultSqlData(){
    QSqlQuery query;
    query.exec("create table logs (id int primary key, "
               "code varchar(20), name varchar(20), date datetime, success int)");
    query.exec("insert into logs values(1, '123', 'Piotrek Room 3', datetime('now'), 1)");
    query.exec("insert into logs values(2, '65566', 'Waldek Room 31', datetime('now'), 0)");
    return 0;
}

static bool addEventToLog(QString code, QString name, QString success){
    QSqlQuery query;
    QString nquery;
    std::cout << nquery.toStdString();
    nquery = "insert into logs (code,name,date,success) values ('" + code + "','" + name +"', datetime('now'), '" + success +"')";
    query.exec(nquery);
    return 0;
}

static bool clearLogDb(){
    QSqlQuery query;
    query.exec("DELETE FROM logs");
    return 0;
}

//! [0]

#endif
