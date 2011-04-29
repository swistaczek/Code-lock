#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("Hello world"));

    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    thread = new CheckThread();
    rb = new RelayB("/dev/ttyUSB0");

    connect(thread, SIGNAL(getPassword()), this, SLOT(goodPassword()));
    connect(thread, SIGNAL(getBadPassword()), this, SLOT(badPassword()));
    connect(thread, SIGNAL(enteredValue(QString input)), this, SLOT(enteredValue(QString input)));

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
    setMinimumSize(160, 160);
    resize(480, 320);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}


void MainWindow::reloadKeyboard()
{
    infoLabel->setText(QString("Keyboard reloaded"));
    thread->reinitializeController();
}

void MainWindow::open()
{
    infoLabel->setText(tr("Blah"));
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
            value);
}

void MainWindow::badPassword()
{
    QMessageBox::about(this, tr("Password"),
            tr("Bad password"));
}

void MainWindow::goodPassword()
{
    rb.revertPort(0);
    QMessageBox::about(this, tr("Password"),
            tr("Good password"));
}

void MainWindow::resetKeyboard()
{
    QMessageBox::about(this, tr("Ok"),
            tr("Keyboard has ben reloaded"));
}

void MainWindow::aboutQt()
{
    infoLabel->setText(tr("About Qt?"));
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

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


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
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
