#ifndef NEWEMPLOYEEWIDGET_H
#define NEWEMPLOYEEWIDGET_H

#include <QtWidgets>
#include <QObject>

class NewEmployeeWidget : public QWidget
{
    Q_OBJECT
public:
     NewEmployeeWidget(QWidget *parent = nullptr);

    ~NewEmployeeWidget();

public slots:
    void checkLines();
    void addEmp();

signals:
    void dataEmployee(QString,QString,QString,QString,int);
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


};

#endif // NEWEMPLOYEEWIDGET_H
