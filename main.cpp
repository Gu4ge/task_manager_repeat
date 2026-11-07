#include "TaskManager.h"

#include <cassert>
#include <iostream>

#include "TaskManager.h"
#include "Notifier.h"

#include <iostream>

int main()
{
    TaskManager manager;

    manager.addNotifier(
        std::make_unique<FileNotifier>("events.log")
    );

    manager.addTask("Learn C++");
    manager.completeTask(0);

    return 0;
}