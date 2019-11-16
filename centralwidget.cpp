#include "centralwidget.h"
#include <QDebug>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    _view = new QColumnView();
    _view->setSelectionMode(QAbstractItemView::SingleSelection);
    _view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    _btnAddSub.setText("Add subdivision");
    _btnAddSub.setEnabled(false);

    _lineNameSub.setPlaceholderText("Enter name subdivision");
    _lineNameSub.setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,20}",Qt::CaseInsensitive)));

    _btnAddEmployee.setText("Add employee");
    _btnAddEmployee.setEnabled(false);

    _hLay.addWidget(&_btnAddSub);
    _hLay.addWidget(&_lineNameSub);
    _hLay.addWidget(&_btnAddEmployee);

    _vLay.addLayout(&_hLay);
    _vLay.addWidget(_view);

    setLayout(&_vLay);

    connect(&_lineNameSub, &QLineEdit::textChanged, this, &CentralWidget::checkSubName);
    connect(&_btnAddSub, &QPushButton::clicked, this, &CentralWidget::sendSignal);
    connect(&_btnAddEmployee, &QPushButton::clicked, this, &CentralWidget::sendSignal);

}

void CentralWidget::checkSubName()
{
    if(!_lineNameSub.text().isEmpty())
        _btnAddSub.setEnabled(true);
    else
    {
        _btnAddSub.setEnabled(false);
    }
}

void CentralWidget::sendSignal()
{
    if(sender() == &_btnAddSub) emit SubName(_lineNameSub.text());

    else if (sender() == &_btnAddEmployee)
    {
        QVariant curSubName(_view->model()->itemData(_view->selectionModel()->selectedIndexes().first()).first());
        emit curSub(curSubName.toString());
        emit addEmp();
    }

    connect(_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CentralWidget::setBtn);

}

void CentralWidget::setBtn()
{
    _btnAddEmployee.setEnabled(true);
}


QColumnView *CentralWidget::view() const
{
    return _view;
}


