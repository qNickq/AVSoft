#include "newcompanywidget.h"
#include "mainwindow.h"
#include "company.h"

NewCompanyWidget::NewCompanyWidget(QWidget *parent) : QWidget(parent)
{
    _btnPath.setText("Path");

    _btnCreate.setText("Create");
    _btnCreate.setEnabled(false);

    _lineCompanyName.setPlaceholderText("Company name");
    _lineCompanyName.setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,20}",Qt::CaseInsensitive)));

    _linePath.setPlaceholderText("Path for your XML file");
    _linePath.setText("/Users/qnickq/Documents");
    _linePath.setReadOnly(true);

//*****Layout settings*****//
    _hLay.addWidget(&_linePath);
    _hLay.addWidget(&_btnPath);
    _vLay.addWidget(&_lineCompanyName);
    _vLay.addLayout(&_hLay);
    _vLay.addWidget(&_btnCreate);
    setLayout(&_vLay);

//*****Slot&Signals Connections*****//
    QObject::connect(&_linePath, &QLineEdit::textChanged, this, &NewCompanyWidget::checkCreate);
    QObject::connect(&_lineCompanyName, &QLineEdit::textChanged, this, &NewCompanyWidget::checkCreate);
    QObject::connect(&_btnPath, &QPushButton::clicked, this, &NewCompanyWidget::choosePath);
    QObject::connect(&_btnCreate, &QPushButton::clicked, this, &NewCompanyWidget::createCompany);


}

NewCompanyWidget::~NewCompanyWidget()
{

}

void NewCompanyWidget::choosePath()
{
    QString path = QFileDialog::getExistingDirectory();

    /*QString path = QFileDialog::getSaveFileName(this,
                                               tr("Save Xml"), ".",
                                               tr("Xml files (*.xml)"));*/
    if(!path.isEmpty())
    {
        _linePath.setText(path);
    }
}

void NewCompanyWidget::createCompany()
{
    emit sendData(_lineCompanyName.text(), _linePath.text());
}

void NewCompanyWidget::checkCreate()
{
    if(!_linePath.text().isEmpty() && !_lineCompanyName.text().isEmpty())
    {
        _btnCreate.setEnabled(true);
    }
    else
    {
        _btnCreate.setEnabled(false);
    }
}
