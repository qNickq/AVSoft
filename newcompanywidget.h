#ifndef NEWCOMPANYWIDGET_H
#define NEWCOMPANYWIDGET_H

#include <QtWidgets>
#include <QObject>

class NewCompanyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewCompanyWidget(QWidget *parent = nullptr);
    ~NewCompanyWidget();

public slots:
    void choosePath();
    void createCompany();
    void checkCreate();

signals:
    void sendData(QString, QString);

private:
    QPushButton _btnPath;
    QPushButton _btnCreate;
    QLineEdit _lineCompanyName;
    QLineEdit _linePath;
    QVBoxLayout _vLay;
    QHBoxLayout _hLay;

};

#endif // NEWCOMPANYWIDGET_H
