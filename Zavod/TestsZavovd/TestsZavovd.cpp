#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm> 
#include <cctype>
#include "../Zavod/Employee.h"
#include "../Zavod/Personal.h"
#include "../Zavod/Engineer.h"
#include "../Zavod/Manager.h"
#include "../Zavod/Project.h"
#include "../Zavod/Factory.h"
#include "../Zavod/Employee.cpp"
#include "../Zavod/Personal.cpp"
#include "../Zavod/Engineer.cpp"
#include "../Zavod/Manager.cpp"
#include "../Zavod/Project.cpp"
#include "../Zavod/Factory.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern std::map<std::string, Project*> projectMap; // Объявление внешней переменной

namespace TestsZavovd
{
    //Тесты первого задания
    TEST_CLASS(DriverTests)
    {
    public:

        // Проверяет правильность расчета базовой оплаты водителя
        // Используется формула: оклад * отработанное время
        TEST_METHOD(Driver_CalcBase)
        {
            Driver driver(1, "Test Driver", 300);
            driver.setWorkTime(160);
            int base = driver.calcBase(300, 160);
            Assert::AreEqual(300 * 160, base);
        }

        // Проверяет расчет бонуса водителя (5% от базовой оплаты)
        TEST_METHOD(Driver_CalcBonus)
        {
            Driver driver(1, "Test Driver", 300);
            driver.setWorkTime(160);
            int bonus = driver.calcBonus();
            Assert::AreEqual(static_cast<int>(0.05 * 300 * 160), bonus);
        }

        // Проверяет общий расчет зарплаты водителя:
        // базовая оплата + бонус
        TEST_METHOD(Driver_CalcPayment)
        {
            Driver driver(1, "Test Driver", 300);
            driver.setWorkTime(160);
            driver.calc();
            int expected = 300 * 160 + static_cast<int>(0.05 * 300 * 160);
            Assert::AreEqual(expected, driver.getPayment());
        }

        // Проверяет корректность работы геттеров:
        // ID, имя, должность и оклад
        TEST_METHOD(Driver_Getters)
        {
            Driver driver(1, "Test Driver", 300);
            Assert::AreEqual(1, driver.getId());
            Assert::AreEqual(std::string("Test Driver"), driver.getName());
            Assert::AreEqual(std::string("Driver"), driver.getPosition());
            Assert::AreEqual(300, driver.getSalary());
        }
    };

    TEST_CLASS(CleanerTests)
    {
    public:
        // Проверяет расчет базовой оплаты уборщика
        // Формула: оклад * отработанное время
        TEST_METHOD(Cleaner_CalcBase)
        {
            Cleaner cleaner(1, "Test Cleaner", 200);
            cleaner.setWorkTime(160);
            int base = cleaner.calcBase(200, 160);
            Assert::AreEqual(200 * 160, base);
        }

        // Проверяет общий расчет зарплаты уборщика
        // Уборщик не получает бонусов, зарплата = базовая оплата
        TEST_METHOD(Cleaner_CalcPayment)
        {
            Cleaner cleaner(1, "Test Cleaner", 200);
            cleaner.setWorkTime(160);
            cleaner.calc();
            Assert::AreEqual(200 * 160, cleaner.getPayment());
        }

        // Проверяет корректность работы геттеров
        TEST_METHOD(Cleaner_Getters)
        {
            Cleaner cleaner(1, "Test Cleaner", 200);
            Assert::AreEqual(1, cleaner.getId());
            Assert::AreEqual(std::string("Test Cleaner"), cleaner.getName());
            Assert::AreEqual(std::string("Cleaner"), cleaner.getPosition());
            Assert::AreEqual(200, cleaner.getSalary());
        }
    };

    TEST_CLASS(TesterTests)
    {
    public:
        // Проверяет фиксированную надбавку для тестировщика (3000)
        TEST_METHOD(Tester_CalcProAdditions)
        {
            Tester tester(1, "Test Tester", 400, nullptr);
            Assert::AreEqual(3000, tester.calcProAdditions());
        }

        // Проверяет полный расчет зарплаты тестировщика при работе над проектом:
        // базовая оплата + доля от бюджета проекта (8%) + фиксированная надбавка
        TEST_METHOD(Tester_CalcWithProject)
        {
            Project proj("TestProj", 100000);
            Tester tester(1, "Test Tester", 400, &proj);
            tester.setWorkTime(160);
            tester.calc();
            int expected = 400 * 160 + static_cast<int>(0.08f * 100000) + 3000;
            Assert::AreEqual(expected, tester.getPayment());
        }

        // Проверяет расчет зарплаты тестировщика без проекта:
        // базовая оплата + фиксированная надбавка
        TEST_METHOD(Tester_CalcWithoutProject)
        {
            Tester tester(1, "Test Tester", 400, nullptr);
            tester.setWorkTime(160);
            tester.calc();
            int expected = 400 * 160 + 3000;
            Assert::AreEqual(expected, tester.getPayment());
        }

        // Проверяет работу с проектом:
        // - Назначение проекта через setProject()
        // - Получение проекта через getProject()
        TEST_METHOD(Tester_ProjectManagement)
        {
            Project proj("TestProj", 100000);
            Tester tester(1, "Test Tester", 400, nullptr);
            tester.setProject(&proj);
            Assert::IsNotNull(tester.getProject());
            Assert::AreEqual(std::string("TestProj"), tester.getProject()->getId());
        }
    };

    TEST_CLASS(ProgrammerTests)
    {
    public:
        // Проверяет фиксированную надбавку для программиста (5000)
        TEST_METHOD(Programmer_CalcProAdditions)
        {
            Programmer programmer(1, "Test Prog", 500, nullptr);
            Assert::AreEqual(5000, programmer.calcProAdditions());
        }

        // Проверяет полный расчет зарплаты программиста при работе над проектом:
        // базовая оплата + доля от бюджета проекта (10%) + фиксированная надбавка
        TEST_METHOD(Programmer_CalcWithProject)
        {
            Project proj("TestProj", 100000);
            Programmer programmer(1, "Test Prog", 500, &proj);
            programmer.setWorkTime(160);
            programmer.calc();
            int expected = 500 * 160 + static_cast<int>(0.1f * 100000) + 5000;
            Assert::AreEqual(expected, programmer.getPayment());
        }

        // Проверяет расчет зарплаты программиста без проекта:
        // базовая оплата + фиксированная надбавка
        TEST_METHOD(Programmer_CalcWithoutProject)
        {
            Programmer programmer(1, "Test Prog", 500, nullptr);
            programmer.setWorkTime(160);
            programmer.calc();
            int expected = 500 * 160 + 5000;
            Assert::AreEqual(expected, programmer.getPayment());
        }
    };

    TEST_CLASS(TeamLeaderTests)
    {
    public:
        // Проверяет надбавку за руководство командой (2000)
        TEST_METHOD(TeamLeader_CalcHeads)
        {
            TeamLeader tl(1, "Test TL", 600, nullptr);
            Assert::AreEqual(2000, tl.calcHeads());
        }

        // Проверяет полный расчет зарплаты тимлида при работе над проектом:
        // базовая оплата + доля от бюджета проекта (15%) + 
        // надбавка программиста + надбавка за руководство
        TEST_METHOD(TeamLeader_CalcWithProject)
        {
            Project proj("TestProj", 100000);
            TeamLeader tl(1, "Test TL", 600, &proj);
            tl.setWorkTime(160);
            tl.calc();
            int expected = 600 * 160 + static_cast<int>(0.15f * 100000) + 5000 + 2000;
            Assert::AreEqual(expected, tl.getPayment());
        }

        // Проверяет расчет зарплаты тимлида без проекта:
        // базовая оплата + надбавка программиста + надбавка за руководство
        TEST_METHOD(TeamLeader_CalcWithoutProject)
        {
            TeamLeader tl(1, "Test TL", 600, nullptr);
            tl.setWorkTime(160);
            tl.calc();
            int expected = 600 * 160 + 5000 + 2000;
            Assert::AreEqual(expected, tl.getPayment());
        }
    };

    TEST_CLASS(ProjectManagerTests)
    {
    public:
        // Проверяет надбавку за руководство проектом (3000)
        TEST_METHOD(ProjectManager_CalcHeads)
        {
            ProjectManager pm(1, "Test PM", 700, nullptr);
            Assert::AreEqual(3000, pm.calcHeads());
        }

        // Проверяет расчет зарплаты PM при работе над проектом:
        // доля от бюджета проекта (20%) + надбавка за руководство
        // Обратите внимание: базовая оплата (оклад * время) не учитывается!
        TEST_METHOD(ProjectManager_CalcWithProject)
        {
            Project proj("TestProj", 100000);
            ProjectManager pm(1, "Test PM", 700, &proj);
            pm.calc();
            int expected = static_cast<int>(0.2f * 100000) + 3000;
            Assert::AreEqual(expected, pm.getPayment());
        }

        // Проверяет расчет зарплаты PM без проекта:
        // только надбавка за руководство
        TEST_METHOD(ProjectManager_CalcWithoutProject)
        {
            ProjectManager pm(1, "Test PM", 700, nullptr);
            pm.calc();
            Assert::AreEqual(3000, pm.getPayment());
        }
    };

    TEST_CLASS(SeniorManagerTests)
    {
    public:
        // Проверяет фиксированную зарплату старшего менеджера (40000)
        // Независимо от времени работы или проектов
        TEST_METHOD(SeniorManager_CalcPayment)
        {
            SeniorManager sm(1, "Test Senior", 1000);
            sm.calc();
            Assert::AreEqual(40000, sm.getPayment());
        }

        // Проверяет корректность работы геттеров
        // Особое внимание: должность должна быть "SeniorManager"
        TEST_METHOD(SeniorManager_Getters)
        {
            SeniorManager sm(1, "Test Senior", 1000);
            Assert::AreEqual(1, sm.getId());
            Assert::AreEqual(std::string("Test Senior"), sm.getName());
            Assert::AreEqual(std::string("SeniorManager"), sm.getPosition());
            Assert::AreEqual(1000, sm.getSalary());
        }
    };
}

namespace FileOperationTests
{
    TEST_CLASS(StaffFactoryFileTests)
    {
    public:
        // Вспомогательная функция для создания тестового файла
        void CreateTestFile(const std::string& filename, const std::string& content) {
            std::ofstream file(filename);
            file << content;
            file.close();
        }

        // Тест проверяет корректность загрузки сотрудников из файла
        TEST_METHOD(TestLoadStaffFromFile)
        {
            // Подготовка тестового файла
            const std::string testFile = "test_staff.txt";
            CreateTestFile(testFile,
                "1;Ivanov Ivan;Programmer;500;Alpha;\n"
                "2;Petrov Petr;Cleaner;200;;\n"
                "3;Sidorov Sidor;Tester;400;Beta;\n"
            );

            // Загрузка сотрудников
            std::vector<Employee*> staff = StaffFactory::makeStaff(testFile);

            // Проверки
            Assert::AreEqual(size_t(3), staff.size());

            // Проверка первого сотрудника (Programmer)
            Assert::AreEqual(1, staff[0]->getId());
            Assert::AreEqual(std::string("Ivanov Ivan"), staff[0]->getName());
            Assert::AreEqual(std::string("Programmer"), staff[0]->getPosition());
            Assert::IsNotNull(dynamic_cast<Programmer*>(staff[0]));

            // Проверка проекта у Programmer
            Engineer* eng = dynamic_cast<Engineer*>(staff[0]);
            Assert::IsNotNull(eng->getProject());
            Assert::AreEqual(std::string("Alpha"), eng->getProject()->getId());

            // Проверка второго сотрудника (Cleaner)
            Assert::AreEqual(2, staff[1]->getId());
            Assert::AreEqual(std::string("Petrov Petr"), staff[1]->getName());
            Assert::IsNull(dynamic_cast<Engineer*>(staff[1])); // Не должен быть инженером

            // Очистка
            for (auto& emp : staff) delete emp;
            projectMap.clear();
            std::remove(testFile.c_str());
        }

        // Тест проверяет корректность сохранения данных в файл
        TEST_METHOD(TestSaveStaffToFile)
        {
            // Подготовка тестовых данных
            Project* alphaProj = new Project("Alpha", 100000);
            projectMap["Alpha"] = alphaProj;

            std::vector<Employee*> staff = {
                new Programmer(1, "Ivanov Ivan", 500, alphaProj),
                new Cleaner(2, "Petrov Petr", 200),
                new Tester(3, "Sidorov Sidor", 400, nullptr)
            };

            // Сохранение в файл
            const std::string outFile = "saved_staff.txt";
            StaffFactory::saveToFile(outFile, staff);

            // Проверка содержимого файла
            std::ifstream in(outFile);
            std::stringstream buffer;
            buffer << in.rdbuf();
            std::string content = buffer.str();

            // Ожидаемое содержимое
            std::string expected =
                "1;Ivanov Ivan;Programmer;500;Alpha;\n"
                "2;Petrov Petr;Cleaner;200;;\n"
                "3;Sidorov Sidor;Tester;400;;\n";

            Assert::AreEqual(expected, content);

            // Очистка
            for (auto& emp : staff) delete emp;
            delete alphaProj;
            projectMap.clear();
            std::remove(outFile.c_str());
        }

        // Тест проверяет обработку пустого файла
        TEST_METHOD(TestEmptyFile)
        {
            const std::string emptyFile = "empty_staff.txt";
            CreateTestFile(emptyFile, ""); // Создаем пустой файл

            std::vector<Employee*> staff = StaffFactory::makeStaff(emptyFile);
            Assert::IsTrue(staff.empty());

            std::remove(emptyFile.c_str());
        }
    };
}

namespace HighLevelTests
{
    TEST_CLASS(ApplicationIntegrationTests)
    {
    public:
        TEST_METHOD(FullCycle_LoadCalculateSave)
        {
            // 1. Подготовка тестового файла
            const std::string testFile = "full_cycle_test.txt";
            std::ofstream(testFile) <<
                "1;Ivanov Ivan;Programmer;500;Alpha;\n"
                "2;Petrova Anna;Cleaner;200;;\n"
                "3;Sidorov Alex;ProjectManager;700;Beta;\n";

            // 2. Загрузка сотрудников
            auto staff = StaffFactory::makeStaff(testFile);

            // 3. Установка рабочего времени и расчет зарплат
            for (auto& emp : staff) {
                emp->setWorkTime(160); // 160 часов для всех
                emp->calc();
            }

            // 4. Проверка расчетов
            // Программист: база + доля проекта + бонус
            Assert::AreEqual(500 * 160 + 10000 + 5000, staff[0]->getPayment());
            // Уборщик: только базовая ставка
            Assert::AreEqual(200 * 160, staff[1]->getPayment());
            // Менеджер: доля проекта + бонус
            Assert::AreEqual(static_cast<int>(0.2f * 100000) + 3000, staff[2]->getPayment());

            // 5. Сохранение изменений
            StaffFactory::saveToFile(testFile, staff);

            // 6. Проверка сохраненных данных
            std::ifstream fin(testFile);
            std::string line;
            std::getline(fin, line);
            Assert::AreEqual(std::string("1;Ivanov Ivan;Programmer;500;Alpha;"), line);

            // Очистка
            for (auto& emp : staff) delete emp;
            projectMap.clear();
            std::remove(testFile.c_str());
        }

        TEST_METHOD(ProjectManagement_AddAndMoveEmployees)
        {
            // 1. Создание тестовых данных
            Project* alpha = new Project("Alpha", 100000);
            Project* beta = new Project("Beta", 150000);
            projectMap["Alpha"] = alpha;
            projectMap["Beta"] = beta;

            std::vector<Employee*> staff = {
                new Programmer(1, "Dev1", 500, alpha),
                new Tester(2, "Tester1", 400, nullptr),
                new ProjectManager(3, "PM1", 700, alpha)
            };

            // 2. Добавление тестировщика в проект Beta
            StaffFactory::addToProject(staff[1], beta);

            // 3. Проверка назначения
            Engineer* tester = dynamic_cast<Engineer*>(staff[1]);
            Assert::IsNotNull(tester->getProject());
            Assert::AreEqual(std::string("Beta"), tester->getProject()->getId());

            // 4. Перевод менеджера с Alpha на Beta
            StaffFactory::moveToProject(staff[2], beta);

            // 5. Проверка перевода
            Engineer* pm = dynamic_cast<Engineer*>(staff[2]);
            Assert::AreEqual(std::string("Beta"), pm->getProject()->getId());

            // Очистка
            for (auto emp : staff) delete emp;
            delete alpha;
            delete beta;
            projectMap.clear();
        }

        TEST_METHOD(SearchFunctionality_ByNameAndProject)
        {
            // 1. Создание тестовых данных
            Project* alpha = new Project("Alpha", 100000);
            projectMap["Alpha"] = alpha;

            std::vector<Employee*> staff = {
                new Programmer(1, "Ivan Ivanov", 500, alpha),
                new Cleaner(2, "Anna Petrova", 200),
                new Tester(3, "Ivan Sidorov", 400, alpha),
                new ProjectManager(4, "Elena Ivanova", 700, alpha)
            };

            // 2. Поиск по части имени "Ivan"
            std::vector<Employee*> foundByName;
            for (auto emp : staff) {
                std::string name = emp->getName();
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                if (name.find("ivan") != std::string::npos) {
                    foundByName.push_back(emp);
                }
            }

            // 3. Проверка поиска по имени
            Assert::AreEqual(size_t(3), foundByName.size());
            Assert::AreEqual(1, foundByName[0]->getId());
            Assert::AreEqual(3, foundByName[1]->getId());
            Assert::AreEqual(4, foundByName[2]->getId());

            // 4. Поиск по проекту Alpha
            std::vector<Employee*> foundByProject;
            for (auto emp : staff) {
                if (auto eng = dynamic_cast<Engineer*>(emp)) {
                    if (eng->getProject() && eng->getProject()->getId() == "Alpha") {
                        foundByProject.push_back(emp);
                    }
                }
            }

            // 5. Проверка поиска по проекту
            Assert::AreEqual(size_t(3), foundByProject.size());
            Assert::AreEqual(1, foundByProject[0]->getId());
            Assert::AreEqual(3, foundByProject[1]->getId());
            Assert::AreEqual(4, foundByProject[2]->getId());

            // Очистка
            for (auto emp : staff) delete emp;
            delete alpha;
            projectMap.clear();
        }

        TEST_METHOD(SalaryCalculation_AllEmployeeTypes)
        {
            // 1. Создание проектов
            Project* alpha = new Project("Alpha", 100000);
            projectMap["Alpha"] = alpha;

            // 2. Создание сотрудников разных типов
            Cleaner cleaner(1, "Cleaner1", 200);
            Driver driver(2, "Driver1", 250);
            Programmer programmer(3, "Dev1", 500, alpha);
            Tester tester(4, "Tester1", 400, alpha);
            TeamLeader teamLead(5, "TL1", 600, alpha);
            ProjectManager pm(6, "PM1", 700, alpha);
            SeniorManager senior(7, "Senior1", 1000);

            // 3. Установка рабочего времени
            cleaner.setWorkTime(160);
            driver.setWorkTime(160);
            programmer.setWorkTime(160);
            tester.setWorkTime(160);
            teamLead.setWorkTime(160);
            pm.setWorkTime(0); // Для PM время не учитывается
            senior.setWorkTime(0);

            // 4. Расчет зарплат
            cleaner.calc();
            driver.calc();
            programmer.calc();
            tester.calc();
            teamLead.calc();
            pm.calc();
            senior.calc();

            // 5. Проверка расчетов
            Assert::AreEqual(200 * 160, cleaner.getPayment()); // Чистая база
            Assert::AreEqual(250 * 160 + static_cast<int>(0.05 * 250 * 160), driver.getPayment()); // База + 5%

            // Программист: база + 10% бюджета + бонус
            Assert::AreEqual(500 * 160 + static_cast<int>(0.1f * 100000) + 5000, programmer.getPayment());

            // Тестировщик: база + 8% бюджета + бонус
            Assert::AreEqual(400 * 160 + static_cast<int>(0.08f * 100000) + 3000, tester.getPayment());

            // Тимлид: база + 15% бюджета + бонус программиста + бонус руководства
            Assert::AreEqual(600 * 160 + static_cast<int>(0.15f * 100000) + 5000 + 2000, teamLead.getPayment());

            // PM: 20% бюджета + бонус
            Assert::AreEqual(static_cast<int>(0.2f * 100000) + 3000, pm.getPayment());

            // Старший менеджер: фиксированная ставка
            Assert::AreEqual(40000, senior.getPayment());

            // Очистка
            delete alpha;
            projectMap.clear();
        }

        TEST_METHOD(ProjectCreation_AndAssignment)
        {
            // 1. Создание нового проекта через фабрику
            projectMap["NewProject"] = new Project("NewProject", 200000);

            // 2. Создание сотрудника
            Programmer programmer(1, "NewDev", 550, nullptr);

            // 3. Назначение на проект
            StaffFactory::addToProject(&programmer, projectMap["NewProject"]);

            // 4. Проверка назначения
            Assert::IsNotNull(programmer.getProject());
            Assert::AreEqual(std::string("NewProject"), programmer.getProject()->getId());

            // 5. Проверка расчета зарплаты с новым проектом
            programmer.setWorkTime(160);
            programmer.calc();
            int expected = 550 * 160 + static_cast<int>(0.1f * 200000) + 5000;
            Assert::AreEqual(expected, programmer.getPayment());

            // Очистка
            delete projectMap["NewProject"];
            projectMap.clear();
        }
    };
}