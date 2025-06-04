#pragma once
#include "Personal.h"
#include "Project.h"
#include "Interfaces.h"

class Engineer : public Personal, public ProjectBudget 
{
protected:
    Project* project;

public:
    Engineer(int id, const std::string& name, const std::string& position, int salary, Project* project);
    int getSalary() const override { return salary; }

    // ProjectBudget
    int calcBudgetPart(float part, int budget) override;
    virtual int calcProAdditions() override;

    void setProject(Project* newProject);
    Project* getProject() const;

    Project* getRawProject() const { return project; }
};

// === Специализации ===
class Programmer : public Engineer {
public:
    Programmer(int id, const std::string& name, int salary, Project* project);
    int calcProAdditions() override;
    void calc() override;
};

class Tester : public Engineer {
public:
    Tester(int id, const std::string& name, int salary, Project* project);
    int calcProAdditions() override;
    void calc() override;
};

class TeamLeader : public Programmer, public Heading {
public:
    TeamLeader(int id, const std::string& name, int salary, Project* project);
    int calcHeads() override;
    void calc() override;
};
