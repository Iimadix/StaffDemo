#include "Employee.h"

Employee::Employee(int id, const std::string& name, const std::string& position)
    : id(id), name(name), position(position), worktime(0), payment(0) {}

void Employee::setWorkTime(int hours) {
    worktime = hours;
}

void Employee::printInfo() const 
{
    std::cout << "ID: " << id
        << ", Name: " << name
        << ", Position: " << position
        << ", Worktime: " << worktime
        << ", Payment: " << payment << std::endl;
}

int Employee::getId() const
{
    return id;
}

int Employee::getWorkTime() const {
    return worktime;
}

std::string Employee::getName() const 
{
    return name;
}

std::string Employee::getPosition() const
{
    return position;
}

int Employee::getPayment() const {
    return payment;
}

