#include "TaskManager.h"

int main()
{
    // {
    //     TaskManager manager;

    //     manager.addTask("Learn C++");
    //     manager.addTask("Write MyVector");
    //     manager.addTask("Learn STL");

    //     manager.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("A");
    //     manager.addTask("B");
    //     manager.addTask("C");

    //     manager.removeTask(1);

    //     manager.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Learn C++");
    //     manager.addTask("Write MyVector");

    //     const Task *task = manager.findTask(1);

    //     if (task)
    //     {
    //         std::cout << task->title << '\n';
    //     }

    //     manager.renameTask(1, "Write MyVector properly");
    //     manager.printTasks();

    //     manager.renameTask(100, "Nothing");
    //     manager.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Learn C++");

    //     const Task *task = manager.findTask(100);

    //     if (task)
    //     {
    //         std::cout << task->title << '\n';
    //     }
    //     else
    //     {
    //         std::cout << "Task not found\n";
    //     }
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("A");
    //     manager.addTask("B");
    //     manager.addTask("C");

    //     manager.completeTask(1);

    //     auto completed = manager.getCompletedTasks();
    //     auto pending = manager.getPendingTasks();

    //     std::cout << "completed: " << completed.size() << '\n';
    //     std::cout << "pending: " << pending.size() << '\n';
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("A");
    //     manager.addTask("B");

    //     Task *task = manager.findTask(1);

    //     if (task)
    //     {
    //         task->title = "Changed";
    //     }

    //     manager.printTasks();
    // }

    // {
    //     const TaskManager manager;

    //     const Task *task = manager.findTask(100);

    //     if (!task)
    //     {
    //         std::cout << "Not found\n";
    //     }
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Learn C++");
    //     manager.addTask("Write MyVector");
    //     manager.completeTask(1);

    //     manager.saveToFile("tasks.txt");
    // }

    // {
    //     TaskManager manager;

    //     manager.loadFromFile("tasks.txt");
    //     manager.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Buy | milk");
    //     manager.saveToFile("tasks.txt");

    //     TaskManager loaded;
    //     loaded.loadFromFile("tasks.txt");
    //     loaded.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Existing A"); // 0
    //     manager.addTask("Existing B"); // 1

    //     manager.loadFromFile("tasks.txt", LoadMode::Append);

    //     manager.printTasks();

    //     manager.addTask("After append");
    //     manager.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Existing A"); // id 0
    //     manager.addTask("Existing B"); // id 1

    //     manager.loadFromFile("tasks.txt", LoadMode::Append);

    //     manager.printTasks();

    //     manager.addTask("After append");

    //     std::cout << "After new task:\n";
    //     manager.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Existing A");

    //     manager.loadFromFile("initial.txt", LoadMode::Replace);

    //     std::cout << "Before append:\n";
    //     manager.printTasks();

    //     manager.loadFromFile("tasks.txt", LoadMode::Append);

    //     std::cout << "\nAfter append:\n";
    //     manager.printTasks();

    //     manager.addTask("After append");

    //     std::cout << "\nAfter new task:\n";
    //     manager.printTasks();
    // }

    // {
    //     TaskManager manager;

    //     manager.addTask("Banana"); // id 0
    //     manager.addTask("Apple");  // id 1
    //     manager.addTask("Cherry"); // id 2

    //     manager.completeTask(1);

    //     std::cout << "=== Title ===\n";
    //     manager.sortTasks(SortMode::Title);
    //     manager.printTasks();

    //     std::cout << "\n=== Id ===\n";
    //     manager.sortTasks(SortMode::Id);
    //     manager.printTasks();

    //     std::cout << "\n=== Completed ===\n";
    //     manager.sortTasks(SortMode::Completed);
    //     manager.printTasks();
    // }

    {
        TaskManager manager;

        manager.addTask("Banana");
        manager.addTask("Kiwi");
        manager.addTask("Watermelon");
        manager.addTask("Apple");

        manager.sortTasks(
            [](const Task &lhs, const Task &rhs)
            {
                return lhs.title.size() < rhs.title.size();
            });

        manager.printTasks();
    }
    return 0;
}