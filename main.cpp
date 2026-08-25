#include "TaskManager.h"

int main()
{
    {
        TaskManager manager;

        manager.addTask("Learn C++");
        manager.addTask("Write MyVector");
        manager.addTask("Learn STL");

        manager.printTasks();
    }

    {
        TaskManager manager;

        manager.addTask("A");
        manager.addTask("B");
        manager.addTask("C");

        manager.removeTask(1);

        manager.printTasks();
    }

    {
        TaskManager manager;

        manager.addTask("Learn C++");
        manager.addTask("Write MyVector");

        const Task *task = manager.findTask(1);

        if (task)
        {
            std::cout << task->title << '\n';
        }

        manager.renameTask(1, "Write MyVector properly");
        manager.printTasks();

        manager.renameTask(100, "Nothing");
        manager.printTasks();
    }

    {
        TaskManager manager;

        manager.addTask("Learn C++");

        const Task *task = manager.findTask(100);

        if (task)
        {
            std::cout << task->title << '\n';
        }
        else
        {
            std::cout << "Task not found\n";
        }
    }

    {
        TaskManager manager;

        manager.addTask("A");
        manager.addTask("B");
        manager.addTask("C");

        manager.completeTask(1);

        auto completed = manager.getCompletedTasks();
        auto pending = manager.getPendingTasks();

        std::cout << "completed: " << completed.size() << '\n';
        std::cout << "pending: " << pending.size() << '\n';
    }

    {
        TaskManager manager;

        manager.addTask("A");
        manager.addTask("B");

        Task *task = manager.findTask(1);

        if (task)
        {
            task->title = "Changed";
        }

        manager.printTasks();
    }

    {
        const TaskManager manager;

        const Task *task = manager.findTask(100);

        if (!task)
        {
            std::cout << "Not found\n";
        }
    }

    {
        TaskManager manager;

        manager.addTask("Learn C++");
        manager.addTask("Write MyVector");
        manager.completeTask(1);

        manager.saveToFile("tasks.txt");
    }

    {
        TaskManager manager;

        manager.loadFromFile("tasks.txt");
        manager.printTasks();
    }
    return 0;
}