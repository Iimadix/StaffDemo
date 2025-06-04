#ifndef MANAGER_H
#define MANAGER_H
#include "Engineer.h"

class ProjectManager : public Engineer, public Heading 
{
public:
    ProjectManager(int id, const std::string& name, int salary, Project* project);
    int getSalary() const override { return salary; }
    int calcHeads() override;
    void calc() override;
};

class SeniorManager : public ProjectManager 
{
public:
    SeniorManager(int id, const std::string& name, int salary);
    int getSalary() const override { return salary; }
    void calc() override;
};

#endif // MANAGER_H