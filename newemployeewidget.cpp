#include "newemployeewidget.h"



NewEmployeeWidget::NewEmployeeWidget(QWidget *parent) : QWidget(parent)
{
    _btnAdd.setText("Add");
    _btnAdd.setEnabled(false);

    _btnCancel.setText("Cancel");

    _lineName.setPlaceholderText("Name");
    _lineName.setMaxLength(20);
    _lineName.setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,20}",Qt::CaseInsensitive)));


    _lineSurname.setPlaceholderText("Surname");
    _lineSurname.setMaxLength(20);
    _lineSurname.setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,20}",Qt::CaseInsensitive)));


    _linePatronymic.setPlaceholderText("Patronymic");
    _linePatronymic.setMaxLength(20);
    _linePatronymic.setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,20}",Qt::CaseInsensitive)));


    _linePosition.setPlaceholderText("Position");
    _linePosition.setMaxLength(20);
    _linePosition.setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,20}",Qt::CaseInsensitive)));

    _lineSalary.setPlaceholderText("Salary");
    _lineSalary.setValidator(new QRegExpValidator(QRegExp("[1-9]{1}[0-9]{2,10}")));


    _hLay.addWidget(&_btnAdd);
    _hLay.addWidget(&_btnCancel);

    _vLay.addWidget(&_lineName);
    _vLay.addWidget(&_lineSurname);
    _vLay.addWidget(&_linePatronymic);
    _vLay.addWidget(&_linePosition);
    _vLay.addWidget(&_lineSalary);
    _vLay.addLayout(&_hLay);

    setLayout(&_vLay);

    connect(&_lineName, &QLineEdit::textEdited, this, &NewEmployeeWidget::checkLines);
    connect(&_lineSurname, &QLineEdit::textEdited, this, &NewEmployeeWidget::checkLines);
    connect(&_linePosition, &QLineEdit::textEdited, this, &NewEmployeeWidget::checkLines);
    connect(&_lineSalary, &QLineEdit::textEdited, this, &NewEmployeeWidget::checkLines);
    connect(&_btnAdd, &QPushButton::clicked, this, &NewEmployeeWidget::addEmp);
    connect(&_btnCancel, &QPushButton::clicked, this, &QWidget::close);

}

void NewEmployeeWidget::checkLines()
{
    if(!_lineName.text().isEmpty() && !_lineSurname.text().isEmpty() && !_lineSalary.text().isEmpty() && !_linePosition.text().isEmpty())
    {
        _btnAdd.setEnabled(true);
    }
    else
    {
        _btnAdd.setEnabled(false);
    }
}

void NewEmployeeWidget::addEmp()
{
    emit sendData(_subName, _lineName.text(),_lineSurname.text(),_linePatronymic.text(),_linePosition.text(), _lineSalary.text().toInt());
}

void NewEmployeeWidget::setSubName(const QString &subName)
{
    _subName = subName;
}

NewEmployeeWidget::~NewEmployeeWidget()
{
}
