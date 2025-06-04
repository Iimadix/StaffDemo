#include "Engineer.h"

Engineer::Engineer(int id, const std::string& name, const std::string& position, int salary, Project* project)
    : Personal(id, name, position, salary), project(project) {}

int Engineer::calcBudgetPart(float part, int budget) 
{
    return static_cast<int>(part * budget);
}

int Engineer::calcProAdditions() {
    return 0; // базовая реализация
}

void Engineer::setProject(Project* newProject)
{
    this->project = newProject;
}


Project* Engineer::getProject() const 
{
    return project;
}

// === Programmer ===
Programmer::Programmer(int id, const std::string& name, int salary, Project* project)
    : Engineer(id, name, "Programmer", salary, project) {}

int Programmer::calcProAdditions() {
    return 5000; // фиксированный бонус
}

void Programmer::calc() 
{
    if (project)
        payment = calcBase(salary, worktime) + calcBudgetPart(0.1f, project->getBudget()) + calcProAdditions();
    else
        payment = calcBase(salary, worktime) + calcProAdditions();
}


// === Tester ===
Tester::Tester(int id, const std::string& name, int salary, Project* project)
    : Engineer(id, name, "Tester", salary, project) {}

int Tester::calcProAdditions() 
{
    return 3000;
}

void Tester::calc() 
{
    if (project)
        payment = calcBase(salary, worktime) + calcBudgetPart(0.08f, project->getBudget()) + calcProAdditions();
    else
        payment = calcBase(salary, worktime) + calcProAdditions();
}


// === TeamLeader ===
TeamLeader::TeamLeader(int id, const std::string& name, int salary, Project* project)
    : Programmer(id, name, salary, project) {
    position = "TeamLeader";
}

int TeamLeader::calcHeads() 
{
    return 2000;
}

void TeamLeader::calc() 
{
    if (project)
        payment = calcBase(salary, worktime) + calcBudgetPart(0.15f, project->getBudget()) + calcProAdditions() + calcHeads();
    else
        payment = calcBase(salary, worktime) + calcProAdditions() + calcHeads();
}

