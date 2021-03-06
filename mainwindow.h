#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <keyboard.h>
#include <checkthread.h>
#include <relayb.h>
#include <logview.h>
#include <usersview.h>
#include <QDateTime>
#include <adduser.h>
#include <QWaitCondition>


QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void reloadKeyboard();
    void open();
    void readLogs();
    void about();
    void enteredValue(QString);
    void badPassword();
    void goodPassword();
    void resetKeyboard();
    void truncateLogs();
    void addUser();
    void listUsers();

    void aboutQt();

private:
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *usersMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *logsAct;
    QAction *clearLogsAct;
    QAction *exitAct;
    QAction *listUsersAct;
    QAction *addUserAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;

    CheckThread *thread;
};


#endif
