#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QStandardItem>

class Employee : public QStandardItem
{
public:
    Employee(QString name = "", QString surname = "", QString middleName ="", QString function = "", int salary = 0);

    QString name() const;
    void setName(const QString &value);

    QString surname() const;
    void setSurname(const QString &value);

    QString middleName() const;
    void setMiddleName(const QString &value);

    QString function() const;
    void setFunction(const QString &value);

    int salary() const;
    void setSalary(int value);

    QString id() const;
    void setId(QString id);
    void setData(const QVariant &value, int role = Qt::UserRole + 1);

private:
    QString _name;
    QString _surname;
    QString _middleName;
    QString _function;
    QString _id;

    int _salary;
};

#endif // EMPLOYEE_H
