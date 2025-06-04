#pragma once
#include <string>
#include <iostream>

class Employee
{
protected:
    int id;
    std::string name;
    std::string position;
    int worktime;
    int payment;

public:
    Employee(int id, const std::string& name, const std::string& position);
    virtual ~Employee() = default;

    void setWorkTime(int hours);
    int getWorkTime() const;
    virtual void calc() = 0;

    virtual void printInfo() const;

    int getId() const;
    std::string getName() const;
    std::string getPosition() const;
    virtual int getSalary() const = 0;  // чтобы переопределялся в потомках
    int getPayment() const;

};
