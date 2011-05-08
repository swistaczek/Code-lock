#ifndef ADDUSER_H
#define ADDUSER_H

#include <QWidget>
#include <iostream>
#include <connection.h>
using namespace std;

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QStandardItemModel;
class QTextEdit;
QT_END_NAMESPACE

class AddUser : public QWidget
{
    Q_OBJECT

public:
    AddUser(QWidget *parent = 0);

private slots:
    void saveEntry();

private:
    void setupModel();

    QLabel *nameLabel;
    QLabel *roomLabel;
    QLabel *codeLabel;
    QLineEdit *nameEdit;
    QLineEdit *codeEdit;
    QLineEdit *roomEdit;
//    QSpinBox *ageSpinBox;
//    QPushButton *nextButton;
//    QPushButton *previousButton;
//    QLabel *ageLabel;

    QPushButton *saveButton;
    QPushButton *cancelButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;
};

#endif // ADDUSER_H
