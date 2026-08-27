#include "TaskManager.h"

void TaskManager::addTask(const std::string &task)
{
    if (isValidTitle(task) != true)
    {
        throw std::invalid_argument("Task title cannot contain '|'");
    }
    Task new_task;
    new_task.id = last_id;
    new_task.title = task;
    new_task.completed = false;
    tasks_.push_back(new_task);
    last_id++;
}

void TaskManager::removeTask(int id)
{
    auto new_end = std::remove_if(tasks_.begin(), tasks_.end(),
                                  [id](const Task &target)
                                  {
                                      return target.id == id;
                                  });
    tasks_.erase(new_end, tasks_.end());
}
void TaskManager::completeTask(int id)
{
    auto task = findTask(id);
    if (task != nullptr)
    {
        task->completed = true;
    }
}

void TaskManager::printTasks() const
{
    for (const Task &i : tasks_)
    {
        std::cout << "id: " << i.id << " task: " << i.title << " completed: " << i.completed << std::endl;
    }
}

const Task *TaskManager::findTask(int id) const
{
    auto it = std::find_if(tasks_.begin(), tasks_.end(), [id](const Task &target)
                           { return target.id == id; });
    if (it == tasks_.end())
    {
        return nullptr;
    }
    return &(*it);
}

Task *TaskManager::findTask(int id)
{
    auto it = std::find_if(tasks_.begin(), tasks_.end(), [id](const Task &target)
                           { return target.id == id; });
    if (it == tasks_.end())
    {
        return nullptr;
    }
    return &(*it);
}
void TaskManager::renameTask(int id, const std::string &newTitle)
{
    if (isValidTitle(newTitle) != true)
    {
        throw std::invalid_argument("Task title cannot contain '|'");
    }
    auto target = findTask(id);
    if (target != nullptr)
    {
        target->title = newTitle;
    }
}

std::vector<Task> TaskManager::getCompletedTasks() const
{
    std::vector<Task> comleted_task;
    for (const auto &i : tasks_)
    {
        if (i.completed)
        {
            comleted_task.push_back(i);
        }
    }
    return comleted_task;
}

std::vector<Task> TaskManager::getPendingTasks() const
{
    std::vector<Task> pending_tasks;
    for (const auto &i : tasks_)
    {
        if (!i.completed)
        {
            pending_tasks.push_back(i);
        }
    }
    return pending_tasks;
}

void TaskManager::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename, std::ios_base::out);
    if (file.is_open())
    {
        for (const auto &task : tasks_)
        {
            file << task.id << '|' << task.title << '|' << task.completed << '\n';
        }
    }
    file.close();
}

void TaskManager::loadFromFile(const std::string &filename, LoadMode mode)
{
    std::ifstream file(filename, std::ios_base::in);

    std::string id, title, completed, line;
    std::vector<Task> buff;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            auto first = line.find_first_of('|');
            auto second = line.find_last_of('|');

            if (first == second || first == std::string::npos)
            {
                throw std::invalid_argument("wrong line");
            }

            id = line.substr(0, first);
            title = line.substr(first + 1, second - first - 1);
            completed = line.substr(second + 1);

            if (isValidTitle(title) != true)
            {
                throw std::invalid_argument("Task title cannot contain '|'");
            }

            if (isValidCompleted(completed) != true)
            {
                throw std::invalid_argument("Task completed must be '0' or '1'");
            }

            Task new_task;
            new_task.id = std::stoi(id);
            new_task.title = title;
            new_task.completed = (completed == "1" ? true : false);
            buff.push_back(new_task);
        }
    }
    // буффер заполнен из файла
    if (mode == LoadMode::Replace)
    {
        if (buff.empty())
        {
            tasks_.clear();
            last_id = 0;
        }
        else
        {
            tasks_ = std::move(buff);
            auto it = findMaxElement(tasks_);
            last_id = it->id + 1;
        }
    }
    else
    {
        if (!buff.empty())
        {
            auto it = findMaxElement(tasks_);

            if (it != nullptr)
                last_id = it->id + 1;

            for (auto &task : buff)
            {
                if (!IsEqualId(task.id))
                {
                    task.id = last_id;
                    ++last_id;
                }
            }

            tasks_.reserve(tasks_.size() + buff.size());
            tasks_.insert(
                tasks_.end(),
                std::make_move_iterator(buff.begin()),
                std::make_move_iterator(buff.end()));
        }
    }
    file.close();
}

bool TaskManager::isValidTitle(const std::string &title) const
{
    return !title.empty();
}
bool TaskManager::isValidCompleted(const std::string &completed) const
{
    return (completed == "1" || completed == "0");
}

bool TaskManager::IsEqualId(int id) const
{
    for (const auto &task : tasks_)
    {
        if (task.id == id)
        {
            return false;
        }
    }
    return true;
}

const Task *findMaxElement(const std::vector<Task> &vec)
{
    if (vec.empty())
        return nullptr;

    auto it = std::max_element(
        vec.begin(),
        vec.end(),
        [](const Task &lhs, const Task &rhs)
        {
            return lhs.id < rhs.id;
        });

    return &(*it);
}