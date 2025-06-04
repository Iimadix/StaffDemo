#ifndef PERSONAL_H
#define PERSONAL_H
#include "Employee.h"
#include "Interfaces.h"

class Personal : public Employee, public WorkBaseTime {
protected:
    int salary;

public:
    Personal(int id, const std::string& name, const std::string& position, int salary);
    int calcBase(int salary, int wtime) override;
    int getSalary() const override { return salary; }
    int calcBonus() override;
};

class Cleaner : public Personal {
public:
    Cleaner(int id, const std::string& name, int salary);
    void calc() override;
};

class Driver : public Personal {
public:
    Driver(int id, const std::string& name, int salary);
    int calcBonus() override;
    void calc() override;
};

#endif // PERSONAL_H
