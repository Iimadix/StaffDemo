#ifndef FACTORY_H
#define FACTORY_H
#include <vector>
#include "Employee.h"
#include "Project.h"
#include <map>

extern std::map<std::string, Project*> projectMap;

class StaffFactory
{
public:

    static std::vector<Employee*> makeStaff(const std::string& filename);
    static void addToProject(Employee* emp, Project* project);
    static void moveToProject(Employee* emp, Project* newProject);
    static void saveToFile(const std::string& filename, const std::vector<Employee*>& staff);
    static Project* getProject(const std::string& name);

};

#endif // FACTORY_H
