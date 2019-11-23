#include "centralwidget.h"

#include <department.h>
#include <ui_centralwidget.h>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CentralWidget)
{
    ui->setupUi(this);

    ui->_view->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->_btnAddEmp->setDisabled(true);
    ui->_btnRemoveEmp->setDisabled(true);

    ui->_btnRemoveDep->setDisabled(true);

    connect(ui->_btnAddEmp, SIGNAL(clicked()), this, SIGNAL(addEmployee()));
    connect(ui->_btnRemoveEmp, SIGNAL(clicked()), this, SIGNAL(removeEmployee()));
    connect(ui->_btnRemoveDep, SIGNAL(clicked()), this, SIGNAL(removeDepartment()));
}

void CentralWidget::sendAddDep()
{
    QString s = ui->_lineNameDep->text();
    if(!s.isEmpty())
    {
        emit addDepartment(s);
    }
}

void CentralWidget::sendEditDep()
{
    QString s = ui->_lineName->text();

    if(!s.isEmpty())
    {
        emit editDepartment(s);
    }
}

void CentralWidget::setEnableBtns()
{
    if(ui->_view->selectionModel()->hasSelection())
    {
        _currentIndex = ui->_view->selectionModel()->selectedIndexes().first().siblingAtColumn(0);

        if(_currentIndex.parent() == QModelIndex())
        {
            ui->_btnAddEmp->setEnabled(true);
            ui->_btnRemoveDep->setEnabled(true);
            ui->_btnRemoveEmp->setEnabled(false);

            emit curDepartment(_currentIndex);
        }
        else
        {
            ui->_btnAddEmp->setEnabled(true);
            ui->_btnRemoveEmp->setEnabled(true);
            ui->_btnRemoveDep->setEnabled(false);

            emit curDepartment(_currentIndex.parent());
            emit curEmployee(_currentIndex);
        }
    }
    else
    {
        _currentIndex = QModelIndex();

        ui->_btnAddEmp->setEnabled(false);
        ui->_btnRemoveEmp->setEnabled(false);
        ui->_btnRemoveDep->setEnabled(false);
    }
}

QModelIndex CentralWidget::currentIndex() const
{
    return _currentIndex;
}

void CentralWidget::setDep(QString name , int count, int salary)
{
    ui->_lineName->setText(name);
    ui->_lCount->setText(QString::number(count));
    ui->_lSalary->setText(QString::number(salary));
}

QTreeView *CentralWidget::view() const
{
    return ui->_view;
}

CentralWidget::~CentralWidget()
{
    delete ui;
}
