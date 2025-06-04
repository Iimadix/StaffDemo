#include "Personal.h"

Personal::Personal(int id, const std::string& name, const std::string& position, int salary)
    : Employee(id, name, position), salary(salary) {}

int Personal::calcBase(int salary, int wtime) 
{
    return salary * wtime;
}

int Personal::calcBonus()
{
    return 0;
}

Cleaner::Cleaner(int id, const std::string& name, int salary)
    : Personal(id, name, "Cleaner", salary) {}

void Cleaner::calc()
{
    payment = calcBase(salary, worktime);
}


Driver::Driver(int id, const std::string& name, int salary)
    : Personal(id, name, "Driver", salary) {
}

int Driver::calcBonus() {
    return static_cast<int>(0.05 * calcBase(salary, worktime));
}

void Driver::calc() {
    payment = calcBase(salary, worktime) + calcBonus();
}
