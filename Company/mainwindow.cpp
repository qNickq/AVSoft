#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _iterator(_history)
{
    _company = nullptr;
    _currentDep = nullptr;

    _centralWidget = new CentralWidget();

    setCentralWidget(_centralWidget);
    centralWidget()->setEnabled(false);
    statusBar()->show();
    createActions();

    connect(_centralWidget, &CentralWidget::curDepartment, this, &MainWindow::setCurrentDep);
    connect(_centralWidget, &CentralWidget::curEmployee, this, &MainWindow::setCurrentEmp);

    connect(_centralWidget, &CentralWidget::addDepartment, this, &MainWindow::addDepartment);
    connect(_centralWidget, &CentralWidget::addEmployee, this, &MainWindow::openNewEployeeDialog);
    connect(_centralWidget, &CentralWidget::removeEmployee, this, &MainWindow::removeEmployee);
    connect(_centralWidget, &CentralWidget::removeDepartment, this, &MainWindow::removeDepartment);
    connect(_centralWidget, &CentralWidget::editDepartment, this, &MainWindow::editDepartment);

    connect(_centralWidget->view(), &QTreeView::doubleClicked,this, &MainWindow::editCompany);
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));
    QToolBar *fileToolBar = addToolBar(tr("Файл"));


    QAction *newAct = new QAction(tr("Создать"));
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Создать новый файл"));

    connect(newAct, &QAction::triggered, this, &MainWindow::openNewCompanyDialog);

    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);


    QAction *openAct = new QAction(tr("Открыть"));
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Открыть файл"));

    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);


    QAction *saveAct = new QAction(tr("Сохранить"));
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Сохранить файл"));

    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);


    QAction *undo = new QAction(tr("Отменить"));
    undo->setShortcuts(QKeySequence::Undo);
    undo->setStatusTip(tr("Отмена предыдущего действия"));

    connect(undo, &QAction::triggered, this, &MainWindow::undoCommand);

    fileMenu->addAction(undo);
    fileToolBar->addAction(undo);

    QAction *redo = new QAction(tr("Повторить"));
    redo->setShortcuts(QKeySequence::Redo);
    redo->setStatusTip(tr("Повтор отмененного действия"));

    connect(redo, &QAction::triggered, this, &MainWindow::redoCommand);

    fileMenu->addAction(redo);
    fileToolBar->addAction(redo);
}

void MainWindow::addEmployee()
{
    QStringList data = _employeeEditor->getData();

    CmdAddEmployee * cmd = new CmdAddEmployee(_company, _currentDep, data[0], data[1], data[2], data[3], data[4].toInt());
    executeCommand(cmd);

    if(_employeeEditor != nullptr)
    {
        _employeeEditor->disconnect();
        delete _employeeEditor;
    }
}

void MainWindow::editCompany(const QModelIndex &index)
{
    QStandardItem *item = _company->itemFromIndex(index.siblingAtColumn(0));

    if(index.parent() != QModelIndex())
    {
        _currentEmp = static_cast<Employee*>(item);
        _employeeEditor = new EmployeeEditor(_currentEmp);
        _employeeEditor->show();

        connect(_employeeEditor, &EmployeeEditor::accepted, this, &MainWindow::editEmployee);
    }
}

void MainWindow::editEmployee()
{
    QStringList data = _employeeEditor->getData();

    CmdEditEmployee * cmd = new CmdEditEmployee(_company, _currentDep, _currentEmp, data[0], data[1], data[2], data[3], data[4].toInt());
    executeCommand(cmd);

    if(_employeeEditor != nullptr)
    {
        _employeeEditor->disconnect();
        _employeeEditor->deleteLater();
    }

    _centralWidget->setDep(_currentDep->name(), _currentDep->countEmp(), _currentDep->avgSalary());
}

void MainWindow::removeEmployee()
{
    CmdRemoveEmployee * cmd = new CmdRemoveEmployee (_company, _currentDep, _currentEmp);
    executeCommand(cmd);
    _centralWidget->view()->selectionModel()->clearSelection();
}

void MainWindow::openFile()
{

    _pathXML = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            ".",
                                            tr("XML files (*.xml)"));

    QFile xmlFile(_pathXML.toString());

    if(!_pathXML.isEmpty() && xmlFile.open(QIODevice::ReadOnly))
    {

        QXmlStreamReader reader(&xmlFile);
        QString depName;
        QString name;
        QString surname;
        QString middleName;
        QString function;
        int salary = 0;

        while (!reader.atEnd() && reader.readNext())
        {
            if(reader.isStartElement())
            {
                if(reader.name() == "departments")
                {
                    newCompany();
                }
                else if(reader.name() == "department")
                {
                    depName = reader.attributes().value("name").toString().trimmed();

                    if(depName.isEmpty())
                    {
                        _currentDep = _company->addDepartment("Неизвестный отдел");
                    }
                    else
                    {
                        _currentDep = _company->addDepartment(depName);
                    }
                }
                else if(reader.name() == "employment")
                {

                    for (int i = 0; i < 5; ++i)
                    {
                        reader.readNextStartElement();

                        if( reader.name() == "name")
                        {
                            name = reader.readElementText();
                            if(name.isEmpty()) name = "Исправить";
                        }
                        else if ( reader.name() == "surname")
                        {
                            surname = reader.readElementText();
                        }
                        else if ( reader.name() == "middleName")
                        {
                            middleName = reader.readElementText();
                        }
                        else if ( reader.name() == "function")
                        {
                            function = reader.readElementText();
                        }
                        else if ( reader.name() == "salary")
                        {
                            salary = reader.readElementText().toInt();
                        }
                    }
                    _currentDep->addEmployee(name,surname,middleName,function,salary);
                }
            }

        }
    }
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

            if(!_company->departments()->isEmpty())
            {
                writer.writeStartDocument();
                writer.writeStartElement("departments");

                QMapIterator<QString, Department*> i (*_company->departments());

                while(i.hasNext())
                {
                    i.next();

                    Department *department = i.value();

                    writer.writeStartElement("department");

                    writer.writeAttribute("name", department->name());

                    QMapIterator<QString, Employee*> it (*department->employees());

                    writer.writeStartElement("employments");

                    while(it.hasNext())
                    {
                        it.next();

                        Employee * employee = it.value();

                        writer.writeStartElement("employment");

                        writer.writeTextElement("surname", employee->surname());
                        writer.writeTextElement("name", employee->name());
                        writer.writeTextElement("middleName", employee->middleName());
                        writer.writeTextElement("function", employee->function());
                        writer.writeTextElement("salary", QString::number(employee->salary()));

                        writer.writeEndElement();
                    }
                    writer.writeEndElement();
                    writer.writeEndElement();
                }
                writer.writeEndElement();

                writer.writeEndDocument();

                xmlFile.close();
            }
            else
            {
                writer.writeStartDocument();
                writer.writeEndDocument();
                xmlFile.close();
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
            saveFile();
            newCompany();
        }
        else
        {
            saveFile();

            delete _company;

            clearHistory();

            newCompany();
        }
    }
    else
    {
        return;
    }
}

void MainWindow::newCompany()
{
    if(!_history.isEmpty())
    {
        clearHistory();
    }

    _company = new Company();

    _centralWidget->view()->setModel(_company);

    centralWidget()->setEnabled(true);

    connect(_centralWidget->view()->selectionModel(), &QItemSelectionModel::selectionChanged, _centralWidget, &CentralWidget::setEnableBtns);

}

void MainWindow::openNewEployeeDialog()
{
    _employeeEditor = new EmployeeEditor();
    connect(_employeeEditor, &EmployeeEditor::accepted, this, &MainWindow::addEmployee);
    _employeeEditor->show();
}

void MainWindow::setCurrentDep(const QModelIndex &index)
{
    _currentDep = static_cast<Department*>(_company->itemFromIndex(index));
    _centralWidget->setDep(_currentDep->name(), _currentDep->countEmp(), _currentDep->avgSalary());
}

void MainWindow::setCurrentEmp(const QModelIndex &index)
{
    _currentEmp = static_cast<Employee*>(_company->itemFromIndex(index));
}

void MainWindow::addDepartment(QString name)
{
    if(!_company->departments()->count(name))
    {
        CmdAddDepartment * cmd = new CmdAddDepartment (_company, name);
        executeCommand(cmd);
    }
    else
    {
        this->statusBar()->showMessage("Такой отдел уже существует!");
    }

}

void MainWindow::editDepartment(QString name)
{
    if(!_company->departments()->count(name))
    {
        CmdEditDepartment * cmd = new CmdEditDepartment(_company, _currentDep, name);
        executeCommand(cmd);
        _centralWidget->setDep(_currentDep->name(), _currentDep->countEmp(), _currentDep->avgSalary());
    }
    else
    {
        this->statusBar()->showMessage("Такой отдел уже существует!");
    }
}

void MainWindow::removeDepartment()
{
    CmdRemoveDepartment * cmd = new CmdRemoveDepartment(_company, _currentDep);
    executeCommand(cmd);
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
             _centralWidget->setDep(_currentDep->name(), _currentDep->countEmp(), _currentDep->avgSalary());
        }
    }

}

void MainWindow::redoCommand()
{
    if(!_history.isEmpty())
    {
        if(_iterator.hasNext())
        {
            _iterator.next()->execute();
            _centralWidget->setDep(_currentDep->name(), _currentDep->countEmp(), _currentDep->avgSalary());
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

MainWindow::~MainWindow()
{
    saveFile();
    _centralWidget->disconnect();
    clearHistory();
    delete _company;
}

