#include "Factory.h"
#include "Engineer.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <map>
extern std::map<std::string, Project*> projectMap;

void printMenu() 
{
    std::cout << "\n=== МЕНЮ ===\n";
    std::cout << "1. Показать всех сотрудников\n";
    std::cout << "2. Показать сотрудников по проекту\n";
    std::cout << "3. Поиск по имени\n";
    std::cout << "4. Поиск по должности\n";
    std::cout << "5. Поиск по зарплате больше/меньше\n";
    std::cout << "6. Создать новый проект\n";
    std::cout << "7. Добавить сотрудника в проект\n";
    std::cout << "8. Перевести сотрудника в другой проект\n";
    std::cout << "9. Сохранить и выйти\n";
    std::cout << "Выберите пункт: ";
}

int main() 
{

    setlocale(LC_ALL, "RUS");
    std::vector<Employee*> staff = StaffFactory::makeStaff("data/staff.txt");

    // Назначение отработанных часов и расчёт зарплаты
    for (auto emp : staff)
    {
        int worktime;
        std::cout << "Введите отработанное время для " << emp->getName() << ": ";
        std::cin >> worktime;
        emp->setWorkTime(worktime);
        emp->calc();
    }

    bool running = true;
    while (running)
    {
        printMenu();
        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Вывод всех сотрудников
        switch (choice)
        {
        case 1: {
            for (auto emp : staff) emp->printInfo();
            break;
        }
        
        // Вывод всех сотрудников по проекту
        case 2: {
            std::cout << "Введите название проекта: ";
            std::string input;
            std::cin >> input;
            for (auto emp : staff) 
            {
                if (Engineer* eng = dynamic_cast<Engineer*>(emp)) 
                {
                    Project* proj = eng->getProject();
                    if (proj && proj->getId() == input) 
                    {
                        emp->printInfo();
                    }
                }
            }
            break;
        }

        // Поиск по имени (часть имени)
        case 3: { 
            std::string namePart;
            std::cout << "Введите имя (или часть): ";
            std::cin.ignore();
            std::getline(std::cin, namePart);

            std::cout << "\n=== Найденые сотрудники ===\n";
            for (auto emp : staff) 
            {
                std::string fullName = emp->getName();
                std::string lowerFullName = fullName, lowerInput = namePart;
                std::transform(lowerFullName.begin(), lowerFullName.end(), lowerFullName.begin(), ::tolower);
                std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

                if (lowerFullName.find(lowerInput) != std::string::npos)
                    emp->printInfo();
            }
            break;
        }

        // Поиск по должности
        case 4: { 
            std::cout << "Введите должность: ";
            std::string input;
            std::cin >> input;

            std::cout << "\n=== Найденые сотрудники по должности " << input << " ===\n";

            for (auto emp : staff) 
            {
                if (emp->getPosition() == input) 
                {
                    emp->printInfo();
                }
            }
            break;
        }

        // Поиск по зарплате
        case 5: {
            int amount;
            char op;
            std::cout << "Введите символ сравнения ('<' или '>'): ";
            std::cin >> op;
            std::cout << "Введите сумму: ";
            std::cin >> amount;

            std::cout << "\n=== Сотрудники по запросу ===\n";
            for (auto emp : staff) 
            {
                if ((op == '<' && emp->getPayment() < amount) ||
                    (op == '>' && emp->getPayment() > amount))
                {
                    emp->printInfo();
                }
            }
            break;
        }

        // Создание нового проекта
        case 6: {
            std::cout << "Введите имя проекта: ";
            std::string projName;
            std::cin >> projName;
            std::cout << "Введите бюджет проекта: ";
            int budget;
            std::cin >> budget;
            projectMap[projName] = new Project(projName, budget);
            std::cout << "\n=== Проект " << projName << " добавлен ===\n";
            break;
        }

        // Добавление нового сотрудника в проект
        case 7: {
            int id;
            std::string projName;
            std::cout << "Введите ID сотрудника: ";
            std::cin >> id;
            std::cout << "Введите название проекта: ";
            std::cin >> projName;

            Project* p = StaffFactory::getProject(projName);
            if (!p) {
                std::cout << "Проект не найден!\n";
                continue;
            }

            for (auto emp : staff)
            {
                if (emp->getId() == id) 
                {
                    StaffFactory::addToProject(emp, p);
                    std::cout << "\n=== Сотрудник успешно добавлен в проект === \n";
                }
            }
            break;
        }

        // Перевод сотрудника на другой проект
        case 8: {
            int id;
            std::string projName;
            std::cout << "Введите ID сотрудника: ";
            std::cin >> id;
            std::cout << "Введите имя нового проекта: ";
            std::cin >> projName;

            Employee* emp = nullptr;
            for (auto e : staff) 
            {
                if (e->getId() == id)
                {
                    emp = e;
                    break;
                }
            }

            if (emp && projectMap.count(projName)) {
                StaffFactory::moveToProject(emp, projectMap[projName]);
                std::cout << "\n=== Сотрудник успешно переведен ===\n";
            }
            else {
                std::cout << "Ошибка: сотрудник или проект не найден.\n";
            }
            break;
        }
        
         // Сохранить файл
        case 9: {
            StaffFactory::saveToFile("data/staff.txt", staff);
            running = false;
            break;
        }

        default:
            std::cout << "Неверный ввод\n";
        }
    }

    for (auto emp : staff) delete emp;
    return 0;
}
