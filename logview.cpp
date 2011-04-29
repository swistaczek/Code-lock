#include "logview.h"

logView::logView(QObject *parent) :
    QObject(parent)
{
//    createConnection();

//    QSqlTableModel model;
//    initializeModel(&model);


//    QTableView *view1 = createView(&model, QObject::tr("Table Model (View 1)"));

//    view1->show();
}

QTableView *logView::createView(QSqlQueryModel *model, const QString &title = ""){
    QTableView *view = new QTableView;
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);

    view->setWindowTitle(title);
    return view;
}

void logView::initializeModel(QSqlQueryModel *model){
    model->setQuery("SELECT firstname, lastname FROM person");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Imie"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nazwisko"));
}
