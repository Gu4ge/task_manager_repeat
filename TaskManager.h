#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
#include <memory>
#include <unordered_set>
#include <sstream>
#include <chrono>
#include <optional>
#include <ctime>
#include <iomanip>

#include "Notifier.h"

enum class LoadMode
{
    Replace,
    Append
};

enum class SortMode
{
    Id,
    Title,
    Completed,
    Priority,
    Deadline
};

enum class Priority
{
    Low,
    Medium,
    High
};

struct Task
{
    int id;
    std::string title;
    bool completed;
    Priority priority = Priority::Medium;
    std::optional<std::chrono::system_clock::time_point> deadline;

    bool operator==(const Task &other) const;
    bool operator!=(const Task &other) const;
};

const Task *findMaxElement(const std::vector<Task> &vec);

class TaskManager
{
public:
    TaskManager() = default;
    TaskManager(std::unique_ptr<Notifier> notifier);
    void setNotifier(std::unique_ptr<Notifier> notifier);
    void addTask(const std::string &task, Priority priority = Priority::Medium);
    void removeTask(int id);
    void completeTask(int id);
    void printTasks() const;
    bool hasUniqueIds() const;
    void setPriority(int id, Priority priority);
    void setDeadline(int id, std::chrono::system_clock::time_point deadline);

    template <class Predicate>
    std::vector<Task> findTasks(Predicate pred) const
    {
        std::vector<Task> result;
        std::copy_if(tasks_.begin(), tasks_.end(), std::back_inserter(result), pred);
        return result;
    }

    const Task *findTask(int id) const;
    Task *findTask(int id);
    void renameTask(int id, const std::string &newTitle);
    std::vector<Task> getCompletedTasks() const;
    std::vector<Task> getPendingTasks() const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename, LoadMode mode = LoadMode::Replace);
    void sortTasks(SortMode mode);
    void sortTasks(std::function<bool(const Task &, const Task &)> comp);

    template <class Compare>
    void sortTasks(Compare comp)
    {
        std::sort(tasks_.begin(), tasks_.end(), comp);
    }

    std::vector<Task> getOverdueTasks() const;

private:
    bool isValidTitle(const std::string &title) const;
    bool isValidCompleted(const std::string &completed) const;
    bool isIdUnique(int id, const std::vector<Task> &vec, size_t endIndex) const;
    bool isIdValid(const std::string &idStr) const;
    bool isPriorityValid(const std::string &priority) const;
    bool isOverdue(int id) const;
    std::string priorityToString(Priority priority) const;
    std::string deadlineToString(const std::optional<std::chrono::system_clock::time_point>& deadline) const;

    std::unique_ptr<Notifier> notifier_;
    std::vector<Task> tasks_;
    int last_id = 0;
};