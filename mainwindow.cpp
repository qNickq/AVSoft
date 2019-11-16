#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    _company = nullptr;

    _centralWidget = new CentralWidget();
    _history = new QList<Command*>();

    setCentralWidget(_centralWidget);
    centralWidget()->setEnabled(false);

    createActions();

    connect(_centralWidget, SIGNAL(SubName(QString)), this, SLOT(addSubdivision(QString)));
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


    QAction *saveAct = new QAction("Save");
    openAct->setShortcuts(QKeySequence::Save);
    openAct->setStatusTip(tr("Save file"));

    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);
}



void MainWindow::openCompany()
{

    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                ".",
                                                tr("XML files (*.xml)"));

    if(!file.isEmpty())
    {

    }
}

void MainWindow::openNewCompanyDialog()
{

    _pathXML = QFileDialog::getSaveFileName(this,
                                            tr("Save Xml"), ".",
                                            tr("Xml files (*.xml)"));
    if(_company == nullptr)
    {

        if(_pathXML.isValid())
            newCompany(_pathXML.fileName());
        else
        {
            return;
        }
    }
}

void MainWindow::newCompany(QString name)
{
    _company = new Company(name);

    _centralWidget->view()->setModel(_company);
    centralWidget()->setEnabled(true);
}

void MainWindow::setCurSub(QString currentSubName)
{
    _currentSubName = currentSubName;
}

void MainWindow::addSubdivision(QString name)
{
    if(_company->subdivisions()->count(name) != 0)
    {

    }
    else
    {
        CmdAddSub * cmd = new CmdAddSub (_company, name);
        executeCommand(cmd);
    }
}

void MainWindow::executeCommand(Command *command)
{
    command->execute();
    _history->push(command);
}

void MainWindow::undoCommand()
{

    if(_history)
}


void MainWindow::openNewEmployeeDialog()
{
    connect(&_newEmployeeWidget, SIGNAL(dataEmployee(QString,QString,QString,QString,int)),
            this, SLOT(addEmployee(QString,QString,QString,QString,int)));
    _newEmployeeWidget.show();
}

void MainWindow::addEmployee(QString name, QString surname, QString patronymic, QString position, int salary)
{
    Subdivision * sub = _company->subdivisions()->value(_currentSubName);
    CmdAddEmployee * cmd = new CmdAddEmployee(sub, name,surname,patronymic,position,salary);
    executeCommand(cmd);

}

void MainWindow::createStatusBar()
{

}


bool MainWindow::maybeSave()
{

}

void MainWindow::saveFile()
{
    QFile xmlFile(_pathXML.toString());
    xmlFile.open(QIODevice::WriteOnly);

    QXmlStreamWriter writer(&xmlFile);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("company");

    writer.writeAttribute("name", _pathXML.fileName());

    QMapIterator<QString, Subdivision*> i (*_company->subdivisions());

    while(i.hasNext())
    {
        i.next();

        Subdivision *subdivision = i.value();

        writer.writeStartElement("subdivision");

        writer.writeAttribute("name", subdivision->name());
        writer.writeAttribute("count_employees", QString::number(subdivision->countEmp()));
        writer.writeAttribute("avg_salary", QString::number(subdivision->avgSalary()));

        QMapIterator<int, Employee*> it (*subdivision->employees());

        while(it.hasNext())
        {

            it.next();

            Employee * employee = it.value();


            writer.writeStartElement("employee");

            writer.writeAttribute("name", employee->name());
            writer.writeAttribute("surname", employee->surname());
            writer.writeAttribute("patronymic", employee->patronymic());
            writer.writeAttribute("position", employee->position());

            writer.writeAttribute("salary", QString::number(employee->salary()));

            writer.writeEndElement();
        }
        writer.writeEndElement();

    }
    writer.writeEndElement();
    writer.writeEndDocument();

    xmlFile.close();
}

void MainWindow::setCurrentFile(const QString &fileName)
{

}

MainWindow::~MainWindow()
{

}

