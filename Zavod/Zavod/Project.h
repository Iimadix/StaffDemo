#ifndef PROJECT_H
#define PROJECT_H
#include <string>

class Project {
private:
    std::string id;
    int budget;

public:
    Project(const std::string& id, int budget);
    std::string getId() const;
    int getBudget() const;
};

#endif // PROJECT_H