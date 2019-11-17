#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QObject>
#include <QtWidgets>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();
    QColumnView *view() const;

signals:
    void addEmployee();
    void SubName(QString);
    void curSub(QString);

public slots:
    void checkSubName();
    void sendSignal();
    void setBtn();

private:
    QColumnView * _view;

    QLineEdit _lineNameSub;

    QPushButton _btnAddSub;
    QPushButton _btnAddEmployee;

    QVBoxLayout _vLay;
    QHBoxLayout _hLay;


};

#endif // CENTRALWIDGET_H
