#ifndef NEWEMPLOYEEWIDGET_H
#define NEWEMPLOYEEWIDGET_H

#include <QtWidgets>
#include <QObject>

class NewEmployeeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewEmployeeWidget(QWidget *parent = nullptr);

    ~NewEmployeeWidget();

    void setSubName(const QString &subName);

public slots:
    void checkLines();
    void addEmp();

signals:
    void sendData(QString,QString,QString,QString,QString,int);
private:

    QLineEdit _lineName;
    QLineEdit _lineSurname;
    QLineEdit _linePosition;
    QLineEdit _linePatronymic;
    QLineEdit _lineSalary;

    QPushButton _btnAdd;
    QPushButton _btnCancel;

    QVBoxLayout _vLay;
    QHBoxLayout _hLay;

    QString _subName;

};

#endif // NEWEMPLOYEEWIDGET_H
