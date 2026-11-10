#include "TaskManager.h"

#include <cassert>
#include <iostream>
#include <algorithm>

#include "TaskManager.h"
#include "Notifier.h"

#include <iostream>

template<typename T, typename U>
bool contains(const std::vector<T>& items, const U& value)
{
    return std::any_of(
        items.begin(),
        items.end(),
        [&value](const T &item)
        {
            return item == value;
        });
        
}

template<typename T, typename Predicate>
const T* findFirst(const std::vector<T>& items, Predicate predicate){
    const auto it = std::find_if(items.begin(), items.end(), predicate);
    if (it != items.end()){
        return &(*it);
    }
    return nullptr;
}

int main()
{
    TaskManager manager;

    manager.addNotifier(
        std::make_unique<FileNotifier>("events.log"));

    manager.addTask("Learn C++");
    manager.completeTask(0);

    return 0;
}