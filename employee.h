#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QStandardItem>

class Employee : public QStandardItem
{
public:
    Employee();
    Employee(QString name, QString surname, QString patronymic, QString position, int salary);

    QString getName() const;
    void setName(const QString &value);

    QString getSurname() const;
    void setSurname(const QString &value);

    QString getPatronymic() const;
    void setPatronymic(const QString &value);

    QString getPosition() const;
    void setPosition(const QString &value);

    int getSalary() const;
    void setSalary(int value);


    int getSubdivisionId() const;
    void setSubdivisionId(int subdivisionId);

    int id() const;
    void setId(int id);

private:
    QString _name;
    QString _surname;
    QString _patronymic;
    QString _position;

    int _subdivisionId;
    int _id;
    int _salary;

};

#endif // EMPLOYEE_H
