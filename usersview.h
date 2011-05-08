#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QObject>
#include <QtGui>
#include <QtSql>
#include <connection.h>

class usersView : public QObject
{
    Q_OBJECT
public:
    explicit usersView(QObject *parent = 0);
    void initializeModel(QSqlQueryModel *);
    QTableView *createView(QSqlQueryModel *, const QString &);

signals:

public slots:

private:
     QSqlTableModel *model;
};

#endif // USERSVIEW_H

