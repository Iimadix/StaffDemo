cmake_minimum_required(VERSION 3.10)
project(CompanyStaffTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаг для тестов (опционально)
add_compile_options(-Wall -Wextra -pedantic)

# Подключаем GoogleTest через FetchContent
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.13.0.zip
)

# Отключаем установку тестов GoogleTest, чтобы не устанавливать лишнее
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Добавляем исходники проекта (укажи свои файлы)
set(SOURCES
    src/Driver.cpp
    src/Cleaner.cpp
    src/Tester.cpp
    src/Programmer.cpp
    src/TeamLeader.cpp
    src/ProjectManager.cpp
    src/SeniorManager.cpp
    src/Project.cpp
    src/StaffFactory.cpp
    # добавь остальные cpp файлы здесь
)

# Добавляем заголовочные файлы (не обязательно, для IDE)
set(HEADERS
    include/Driver.h
    include/Cleaner.h
    include/Tester.h
    include/Programmer.h
    include/TeamLeader.h
    include/ProjectManager.h
    include/SeniorManager.h
    include/Project.h
    include/StaffFactory.h
    # остальные заголовки
)

add_executable(tests
    tests/tests.cpp # тут твои тесты
    ${SOURCES}
)

target_include_directories(tests PRIVATE include)

# Линкуем GoogleTest и pthread (на Linux/Unix)
target_link_libraries(tests gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(tests)
