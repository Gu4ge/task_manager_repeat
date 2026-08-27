#include "TaskManager.h"

int main()
{
  

    {
        TaskManager manager;

        manager.addTask("Existing A"); // 0
        manager.addTask("Existing B"); // 1

        manager.loadFromFile("tasks.txt", LoadMode::Append);

        manager.printTasks();

        manager.addTask("After append");
        manager.printTasks();
    }
    return 0;
}