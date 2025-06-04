#include "Factory.h"
#include "Personal.h"
#include "Engineer.h"
#include "Manager.h"
#include <fstream>
#include <sstream>
#include <map>

std::map<std::string, Project*> projectMap;

std::vector<Employee*> StaffFactory::makeStaff(const std::string& filename)
{
    std::vector<Employee*> staff;
    std::ifstream fin(filename);
    std::string line;

    while (std::getline(fin, line)) 
    {
        std::stringstream ss(line);
        std::string idStr, name, position, salaryStr, projectName;
        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, position, ';');
        std::getline(ss, salaryStr, ';');
        std::getline(ss, projectName, ';');

        int id = std::stoi(idStr);
        int salary = std::stoi(salaryStr);
        Project* proj = nullptr;

        if (!projectName.empty())
        {
            if (projectMap.find(projectName) == projectMap.end())
            {
                projectMap[projectName] = new Project(projectName, 100000); // дефолтный бюджет
            }
            proj = projectMap[projectName];
        }

        if (position == "Cleaner")
            staff.push_back(new Cleaner(id, name, salary));
        else if (position == "Driver")
            staff.push_back(new Driver(id, name, salary));
        else if (position == "Programmer")
            staff.push_back(new Programmer(id, name, salary, proj));
        else if (position == "Tester")
            staff.push_back(new Tester(id, name, salary, proj));
        else if (position == "TeamLeader")
            staff.push_back(new TeamLeader(id, name, salary, proj));
        else if (position == "ProjectManager")
            staff.push_back(new ProjectManager(id, name, salary, proj));
        else if (position == "SeniorManager")
            staff.push_back(new SeniorManager(id, name, salary));
    }

    return staff;
}

void StaffFactory::addToProject(Employee* emp, Project* project)
{
    if (Engineer* eng = dynamic_cast<Engineer*>(emp)) {
        eng->setProject(project);
    }
}

void StaffFactory::moveToProject(Employee* emp, Project* newProject)
{
    addToProject(emp, newProject);
}

void StaffFactory::saveToFile(const std::string& filename, const std::vector<Employee*>& staff) 
{
    std::ofstream fout(filename);
    for (Employee* emp : staff) {
        Project* proj = nullptr;
        std::string projName = "";
        if (Engineer* eng = dynamic_cast<Engineer*>(emp)) 
        {
            proj = eng->getProject();
            if (proj) projName = proj->getId();
        }
        fout << emp->getId() << ";" << emp->getName() << ";" << emp->getPosition() << ";"
            << emp->getSalary() << ";" << projName << ";" << std::endl;
    }
}

Project* StaffFactory::getProject(const std::string& name) 
{
    if (projectMap.count(name)) return projectMap[name];
    return nullptr;
}
