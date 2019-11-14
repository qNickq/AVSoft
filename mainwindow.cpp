#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createActions();

    _centralWidget = new CentralWidget();

    setCentralWidget(_centralWidget);
    centralWidget()->setEnabled(false);

    connect(_centralWidget, SIGNAL(addSub(QString)), this, SLOT(addSubdivision(QString)));
    connect(_centralWidget, &CentralWidget::addEmp, this, &MainWindow::openNewEmployeeDialog);
    connect(_centralWidget, SIGNAL(curSub(QString)), this, SLOT(setCurSub(QString)));
}


void MainWindow::createActions()
{

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    QAction *newAct = new QAction("New");
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::openNewCompanyDialog);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);


    QAction *openAct = new QAction("Open");
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openCompany);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);
}



void MainWindow::openCompany()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(".xml");

    QString file = dialog.getOpenFileName();

    if(!file.isEmpty())
    {

    }
}

void MainWindow::openNewCompanyDialog()
{

    connect(&_newCompanyWidget, SIGNAL(sendData(QString, QString)), this, SLOT(newCompany(QString, QString)));

    _newCompanyWidget.show();
}

void MainWindow::newCompany(QString name, QString path)
{
    _company = new Company(name, path);

    _newCompanyWidget.close();

    _centralWidget->view()->setModel(_company);

    centralWidget()->setEnabled(true);
    connect(_company, &Company::go,_centralWidget,&CentralWidget::setName);
}

void MainWindow::setCurSub(QString curSub)
{
    _curSub = curSub;
}

void MainWindow::addSubdivision(QString name)
{
    if(name.isEmpty()) return;
    _company->addSubdivision(name);
}

void MainWindow::openNewEmployeeDialog()
{

    _newEmployeeWidget.setSubName(_curSub);

    connect(&_newEmployeeWidget, SIGNAL(sendData(QString,QString,QString,QString,QString,int)),
            _company, SLOT(addEmployee(QString,QString,QString,QString,QString,int)));
    _newEmployeeWidget.show();
}

void MainWindow::addEmployee()
{

}

void MainWindow::createStatusBar()
{

}

void MainWindow::readSettings()
{

}

void MainWindow::writeSettings()
{

}

bool MainWindow::maybeSave()
{

}

bool MainWindow::saveFile(const QString &fileName)
{

}

void MainWindow::setCurrentFile(const QString &fileName)
{

}

MainWindow::~MainWindow()
{

}
