#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QObject>
#include <QtGui>
#include <QtSql>
#include <connection.h>

class logView : public QObject
{
    Q_OBJECT
public:
    explicit logView(QObject *parent = 0);
    void initializeModel(QSqlQueryModel *);
    QTableView *createView(QSqlQueryModel *, const QString &);

signals:

public slots:

private:
     QSqlTableModel *model;
};

#endif // LOGVIEW_H

