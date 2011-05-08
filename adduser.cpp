#include <QtGui>
#include "adduser.h"

AddUser::AddUser(QWidget *parent)
    : QWidget(parent)
{
    setupModel();

    nameLabel = new QLabel(tr("&Name:"));
    nameEdit = new QLineEdit();
    roomLabel = new QLabel(tr("&Room:"));
    roomEdit = new QLineEdit();
    codeLabel = new QLabel(tr("&Acces code:"));
    codeEdit = new QLineEdit();
    saveButton = new QPushButton(tr("&Save"));
    cancelButton = new QPushButton(tr("&Cancel"));

    nameLabel->setBuddy(nameEdit);
    roomLabel->setBuddy(roomEdit);
    codeLabel->setBuddy(codeEdit);
//! [Set up widgets]

//! [Set up the mapper]
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(nameEdit, 0);
    mapper->addMapping(roomEdit, 1);
    mapper->addMapping(codeEdit, 2);

//    connect(nextButton, SIGNAL(clicked()),
//            mapper, SLOT(toNext()));
//    connect(mapper, SIGNAL(currentIndexChanged(int)),
//            this, SLOT(updateButtons(int)));

    connect(saveButton, SIGNAL(clicked()),
            this, SLOT(saveEntry()));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
//! [Set up the mapper]

//! [Set up the layout]
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(nameLabel, 0, 0, 1, 1);
    layout->addWidget(nameEdit, 0, 1, 1, 1);

    layout->addWidget(roomLabel, 1, 0, 1, 1);
    layout->addWidget(roomEdit, 1, 1, 1, 1);

    layout->addWidget(codeLabel, 2, 0, 1, 1);
    layout->addWidget(codeEdit, 2, 1, 2, 1);

    layout->addWidget(saveButton, 0, 2, 1, 1);
    layout->addWidget(cancelButton, 0, 2, 0, 1);

    setLayout(layout);

    setWindowTitle(tr("Adding user"));
    mapper->toFirst();
}
//! [Set up the layout]

//! [Set up the model]

void AddUser::saveEntry(){
    addUserToUsers(nameEdit->text(), roomEdit->text(), codeEdit->text());
    cout << "-- Added new user: \n";
    cout << "name: " << nameEdit->text().toStdString() << "\n";
    cout << "room: " << roomEdit->text().toStdString() << "\n";
    cout << "code: " << codeEdit->text().toStdString() << "\n";
    cout << "-----------------------------\n";
    close();
}

void AddUser::setupModel()
{
    model = new QStandardItemModel(1, 4, this);

    QStringList names;
    names << "";

    QStringList rooms;
    rooms << "";

    QStringList codes;
    codes<< "";

    QStandardItem *item = new QStandardItem(names[0]);
    model->setItem(0, 0, item);
    item = new QStandardItem(rooms[0]);
    model->setItem(0, 1, item);
    item = new QStandardItem(codes[0]);
    model->setItem(0, 2, item);
}
//! [Set up the model]

//! [Slot for updating the buttons]
//void AddUser::updateButtons(int row)
//{
//    previousButton->setEnabled(row > 0);
//    nextButton->setEnabled(row < model->rowCount() - 1);
//}
//! [Slot for updating the buttons]
