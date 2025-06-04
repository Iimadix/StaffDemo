#include "Project.h"

Project::Project(const std::string& id, int budget) : id(id), budget(budget) {}
std::string Project::getId() const { return id; }
int Project::getBudget() const { return budget; }