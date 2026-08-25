#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

struct Task
{
    int id;
    std::string title;
    bool completed;
};

class TaskManager
{
public:
    TaskManager() = default;
    void addTask(const std::string &task);
    void removeTask(int id);
    void completeTask(int id);
    void printTasks() const;
    const Task *findTask(int id) const;
    Task *findTask(int id);
    void renameTask(int id, const std::string &newTitle);
    std::vector<Task> getCompletedTasks() const;
    std::vector<Task> getPendingTasks() const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);

private:
    std::vector<Task> tasks_;
    int last_id = 0;
};