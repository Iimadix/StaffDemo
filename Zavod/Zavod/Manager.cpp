#include "Manager.h"

ProjectManager::ProjectManager(int id, const std::string& name, int salary, Project* project)
    : Engineer(id, name, "ProjectManager", salary, project) {}

int ProjectManager::calcHeads() 
{
    return 3000;
}

void ProjectManager::calc() 
{
    if (project)
        payment = calcBudgetPart(0.2f, project->getBudget()) + calcHeads();
    else
        payment = calcHeads();
}


SeniorManager::SeniorManager(int id, const std::string& name, int salary)
    : ProjectManager(id, name, salary, nullptr)
{
    position = "SeniorManager"; // Для работы теста
}

void SeniorManager::calc() 
{
    payment = 40000; // заглушка
}