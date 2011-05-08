#include <QtGui>
#include "mainwindow.h"

RelayB relayboard("/dev/ttyUSB0");
MainWindow::MainWindow()
{
    //createDefaultSqlData();
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("System ready"));

    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    thread = new CheckThread();

    connect(thread, SIGNAL(getPassword()), this, SLOT(goodPassword()));
    connect(thread, SIGNAL(getBadPassword()), this, SLOT(badPassword()));
    connect(thread, SIGNAL(enteredValue(QString)), this, SLOT(enteredValue(QString)));

    thread->checkPassword();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    QString message = tr("CodeLock by Ernest Bursa");
    statusBar()->showMessage(message);

    setWindowTitle(tr("CodeLock 0.1"));
    setMinimumSize(100, 100);
    setMaximumSize(300,180);
    resize(300,180);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}


void MainWindow::reloadKeyboard()
{
    QMessageBox::about(this, tr("Ok"), tr("Keyboard has ben reloaded"));
    this->thread->reinitializeController();
}

void MainWindow::open()
{
    infoLabel->setText(tr("Request send"));
    thread->getValue();
}

void MainWindow::readLogs(){
    infoLabel->setText(tr("Read logs"));
    logView logs;
}

void MainWindow::truncateLogs(){
    infoLabel->setText(tr("Logs cleared"));
    clearLogDb();
}

void MainWindow::about()
{
    infoLabel->setText(tr("Find source code @ http://github.com/swistaczek"));
    QMessageBox::about(this, tr("About"),
            tr("CodeLock software could be used as code lock and home maintance software. <br /> Author: <strong>Ernest Bursa</strong> <br />Find source code at <strong>http://github.com/swistaczek</strong> "));
}

void MainWindow::enteredValue(QString value)
{
    QMessageBox::about(this, tr("Entered value"),
            tr("Entered value: ") + value);
}

void MainWindow::badPassword()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateString = dateTime.toString();
    QString message = tr(": Bad password");
    statusBar()->showMessage(dateString + message);
//    QMessageBox::about(this, tr("Password"),
//            tr("Bad password"));
}

void MainWindow::goodPassword()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateString = dateTime.toString();
    QString message = tr(": Good password");
    statusBar()->showMessage(dateString + message);
    for(int i=0; i<4; i++)
        relayboard.openPort(i);
    infoLabel->setText(tr("Lock enabled for 15 sec"));
    QTime dieTime = QTime::currentTime().addSecs(15);
    while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    infoLabel->setText(tr("Lock disabled"));
    for(int i=0; i<4; i++)
        relayboard.closePort(i);
//    QMessageBox::about(this, tr("Password"),
//            tr("Good password"));
}

void MainWindow::resetKeyboard()
{
    QMessageBox::about(this, tr("Ok"), tr("Keyboard has ben reloaded"));
    this->thread->reinitializeController();
}

void MainWindow::aboutQt()
{
    infoLabel->setText(tr("About Qt"));
}

void MainWindow::listUsers(){
    infoLabel->setText(tr("List users"));
    usersView users;
}

void MainWindow::addUser(){
    AddUser *addUserWindow = new AddUser;
    addUserWindow->show();
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&Reset keyboard"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("You could reset USB keyboard module"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(reloadKeyboard()));

    openAct = new QAction(tr("&Get data from keyboard..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Grab keyboard data"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    logsAct = new QAction(tr("&Read logs"), this);
    logsAct->setShortcuts(QKeySequence::Open);
    logsAct->setStatusTip(tr("Read recent data logs"));
    connect(logsAct, SIGNAL(triggered()), this, SLOT(readLogs()));

    clearLogsAct = new QAction(tr("&Clear logs"), this);
    clearLogsAct->setShortcuts(QKeySequence::Open);
    clearLogsAct->setStatusTip(tr("Clear recent data logs"));
    connect(clearLogsAct, SIGNAL(triggered()), this, SLOT(truncateLogs()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    listUsersAct = new QAction(tr("&List users"), this);
    listUsersAct->setStatusTip(tr("Lists all keylock users"));
    connect(listUsersAct, SIGNAL(triggered()), this, SLOT(listUsers()));

    addUserAct = new QAction(tr("&Add user"), this);
    addUserAct->setStatusTip(tr("Ads new user"));
    connect(addUserAct, SIGNAL(triggered()), this, SLOT(addUser()));


    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(logsAct);
    fileMenu->addAction(clearLogsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    usersMenu = menuBar()->addMenu(tr("&Users"));
    usersMenu->addAction(listUsersAct);
    usersMenu->addAction(addUserAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
