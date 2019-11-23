#include "employeeeditor.h"
#include "ui_employeeeditor.h"

EmployeeEditor::EmployeeEditor(Employee *emp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeEditor)
{
    ui->setupUi(this);

    setModal(true);
    _employee = emp;

    ui->_lineName->setValidator(new QRegExpValidator(QRegExp("[A-Я]{0,20}",Qt::CaseInsensitive)));
    ui->_lineSurname->setValidator(new QRegExpValidator(QRegExp("[A-Я]{0,20}",Qt::CaseInsensitive)));
    ui->_lineSurname->setFocus();

    ui->_lineMiddleName->setValidator(new QRegExpValidator(QRegExp("[A-Я]{0,20}",Qt::CaseInsensitive)));
    ui->_lineSalary->setValidator(new QRegExpValidator(QRegExp("[1-9]{1}[0-9]{2,10}")));

    if(_employee != nullptr)
    {
        ui->_lineName->         setText(emp->name());
        ui->_lineSurname->      setText(emp->surname());
        ui->_lineMiddleName->   setText(emp->middleName());
        ui->_lineFunction->     setText(emp->function());
        ui->_lineSalary->       setText(QString::number(emp->salary()));
    }
}

EmployeeEditor::~EmployeeEditor()
{
    delete ui;
}

QStringList EmployeeEditor::getData()
{
    QStringList data;
    data << ui->_lineName->text() << ui->_lineSurname->text() << ui->_lineMiddleName->text()
      << ui->_lineFunction->text() << QString::number(ui->_lineSalary->text().toInt());

    return data;

}
