#include "logview.h"

logView::logView(QObject *parent) :
    QObject(parent)
{
    model = new QSqlTableModel;

    initializeModel(model);

    QTableView *view1 = createView(model, QObject::tr("Table Model (View 1)"));

    view1->show();
}

QTableView *logView::createView(QSqlQueryModel *model, const QString &title = ""){
    QTableView *view = new QTableView;
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    view->setWordWrap(TRUE);
    view->setWindowTitle(title);
    view->setAutoScroll(true);
    view->setWordWrap(true);
    view->resize(421, 300);

    QHeaderView * header = view->horizontalHeader();
    header->stretchLastSection();

    return view;
}

void logView::initializeModel(QSqlQueryModel *model){
    model->setQuery("SELECT code, name, success, date FROM logs ORDER BY id desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Succes?"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
}
