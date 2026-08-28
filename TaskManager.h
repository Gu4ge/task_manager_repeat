#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>

enum class LoadMode
{
    Replace,
    Append
};

struct Task
{
    int id;
    std::string title;
    bool completed;
};

const Task *findMaxElement(const std::vector<Task> &vec);

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
    void loadFromFile(const std::string &filename, LoadMode mode = LoadMode::Replace);

private:
    bool isValidTitle(const std::string &title) const;
    bool isValidCompleted(const std::string &completed) const;
    bool isIdUnique(int id, const std::vector<Task> &vec, size_t endIndex) const;

    std::vector<Task> tasks_;
    int last_id = 0;
};