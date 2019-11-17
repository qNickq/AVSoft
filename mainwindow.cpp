#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _iterator(_history)
{
    _company = nullptr;
    _newEmployeeWidget = nullptr;

    _centralWidget = new CentralWidget();

    setCentralWidget(_centralWidget);
    centralWidget()->setEnabled(false);

    createActions();
    statusBar()->showMessage("Create new or open file");

    connect(_centralWidget, &CentralWidget::SubName, this, &MainWindow::addSubdivision);
    connect(_centralWidget, &CentralWidget::curSub, this, &MainWindow::setCurSub);
    connect(_centralWidget, &CentralWidget::addEmployee, this, &MainWindow::openNewEployeeDialog);

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
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save file"));

    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);


    QAction *undo = new QAction("Undo");
    undo->setShortcuts(QKeySequence::Undo);
    undo->setStatusTip(tr("Undo"));

    connect(undo, &QAction::triggered, this, &MainWindow::undoCommand);

    fileMenu->addAction(undo);
    fileToolBar->addAction(undo);

    QAction *redo = new QAction("Redo");
    redo->setShortcuts(QKeySequence::Redo);
    redo->setStatusTip(tr("Redo"));

    connect(redo, &QAction::triggered, this, &MainWindow::redoCommand);

    fileMenu->addAction(redo);
    fileToolBar->addAction(redo);
}

void MainWindow::openCompany()
{

    _pathXML = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            ".",
                                            tr("XML files (*.xml)"));

    QFile xmlFile(_pathXML.toString());


    if(xmlFile.open(QIODevice::ReadOnly) && !_pathXML.isEmpty() )
    {
        QXmlStreamReader reader(&xmlFile);

        while (!reader.atEnd() && reader.readNext())
        {
            if(reader.isStartElement())
            {
                if(reader.name() == "company")
                {
                    newCompany(reader.attributes().value("name").toString());
                }
                else if(reader.name() == "subdivision")
                {
                    QString subName = reader.attributes().value("name").toString();
                    addSubdivision(subName);
                }
                else if(reader.name() == "employee")
                {
                    QString name = reader.attributes().value("name").toString();
                    QString surname = reader.attributes().value("surname").toString();
                    QString patronymic = reader.attributes().value("patronymic").toString();
                    QString position = reader.attributes().value("position").toString();
                    int salary = reader.attributes().value("salary").toInt();

                    addEmployee(name,surname,patronymic,position,salary);
                }
            }

        }
    }
}

void MainWindow::openNewCompanyDialog()
{

    _pathXML = QFileDialog::getSaveFileName(this, tr("Save Xml"), ".", tr("Xml files (*.xml)"));

    if(_pathXML.isValid())
    {
        if(_company == nullptr)
        {
            newCompany(_pathXML.fileName());
        }
        else
        {
            saveFile();

            delete _company;

            clearHistory();

            newCompany(_pathXML.fileName());
        }
    }
    else
    {
        return;
    }
}

void MainWindow::newCompany(QString name)
{
    _company = new Company(name);
    _centralWidget->view()->setModel(_company);
    centralWidget()->setEnabled(true);

    connect(_centralWidget->view()->selectionModel(), &QItemSelectionModel::selectionChanged, _centralWidget, &CentralWidget::setBtn);

}

void MainWindow::setCurSub(QString currentSubName)
{
    _currentSub = _company->subdivisions()->value(currentSubName);
}

void MainWindow::openNewEployeeDialog()
{
    _newEmployeeWidget = new NewEmployeeWidget();

    connect(_newEmployeeWidget, &NewEmployeeWidget::dataEmployee, this, &MainWindow::addEmployee);

    _newEmployeeWidget->show();
}

void MainWindow::addSubdivision(QString name)
{
    if(_company->subdivisions()->count(name) != 0)
    {
        this->statusBar()->showMessage("This name is already exists");
    }
    else
    {
        CmdAddSub * cmd = new CmdAddSub (_company, name);
        executeCommand(cmd);
        setCurSub(name);
    }
}

void MainWindow::executeCommand(Command *command)
{
    command->execute();
    _history.append(command);
    _iterator = _history;
    _iterator.toBack();

}

void MainWindow::undoCommand()
{

    if(!_history.isEmpty())
    {
        if(_iterator.hasPrevious())
        {
            _iterator.previous()->undo();
        }
    }
}

void MainWindow::redoCommand()
{
    if(!_history.isEmpty())
    {
        if(_iterator.hasNext())
        {
            _iterator.next()->redo();
        }
    }
}

void MainWindow::clearHistory()
{
    for (_iterator.toFront(); _iterator.hasNext();)
    {
        delete _iterator.next();
    }
    _history.clear();
}

void MainWindow::addEmployee(QString name, QString surname, QString patronymic, QString position, int salary)
{
    CmdAddEmployee * cmd = new CmdAddEmployee(_company, _currentSub->name(), name, surname, patronymic, position, salary);
    executeCommand(cmd);

    _newEmployeeWidget->close();
    _newEmployeeWidget->disconnect();
    _newEmployeeWidget->deleteLater();

    _centralWidget->view()->update();

}


void MainWindow::saveFile()
{
    if(_company != nullptr)
    {
        QFile xmlFile(_pathXML.toString());

        if(xmlFile.open(QIODevice::WriteOnly))
        {

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
    }
}


MainWindow::~MainWindow()
{

}

