#include "usersview.h"

usersView::usersView(QObject *parent) :
    QObject(parent)
{
    model = new QSqlTableModel;

    initializeModel(model);

    QTableView *view1 = createView(model, QObject::tr("Users view"));

    view1->show();
}

QTableView *usersView::createView(QSqlQueryModel *model, const QString &title = ""){
    QTableView *view = new QTableView;
    //view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    view->setWordWrap(TRUE);
    view->setWindowTitle(title);
    view->setAutoScroll(true);
    view->setWordWrap(true);
    view->resize(453, 445);

    QHeaderView * header = view->horizontalHeader();
    header->stretchLastSection();

    return view;
}

void usersView::initializeModel(QSqlQueryModel *model){
    model->setQuery("SELECT name, room, code, success_count FROM users ORDER BY id desc LIMIT 150");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Room"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Succes count"));
}
