#include "TaskManager.h"

#include <cassert>
#include <iostream>

int main()
{
    // 1. Создаём менеджер
    TaskManager manager;

    manager.addTask("Learn C++", Priority::High);
    manager.addTask("Learn STL", Priority::Medium);
    manager.addTask("Buy milk", Priority::Low);

    manager.completeTask(1);

    // 2. Сохраняем задачи
    manager.saveToFile("tasks_test.txt");

    // 3. Создаём второй менеджер
    TaskManager loadedManager;

    // 4. Загружаем задачи из файла
    loadedManager.loadFromFile(
        "tasks_test.txt",
        LoadMode::Replace
    );

    // 5. Проверяем количество задач
    auto originalTasks = manager.findTasks(
        [](const Task& task) { return true; }
    );

    auto loadedTasks = loadedManager.findTasks(
        [](const Task& task) { return true; }
    );

    assert(originalTasks.size() == loadedTasks.size());
    assert(loadedTasks.size() == 3);

    // 6. Сравниваем каждую задачу
    for (const auto& original : originalTasks)
    {
        const Task* loaded = loadedManager.findTask(original.id);

        assert(loaded != nullptr);
        assert(original == *loaded);
    }

    // 7. Проверяем уникальность ID
    assert(loadedManager.hasUniqueIds());

    // 8. Проверяем генерацию ID после загрузки
    loadedManager.addTask("New Task", Priority::High);

    const Task* newTask = loadedManager.findTask(3);

    assert(newTask != nullptr);
    assert(newTask->title == "New Task");
    assert(newTask->priority == Priority::High);

    std::cout << "All tests passed!\n";

    return 0;
}