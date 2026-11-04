#include "TaskManager.h"

TaskManager::TaskManager(std::unique_ptr<Notifier> notifier)
    : notifier_(std::move(notifier))
{
}

void TaskManager::addTask(const std::string &task, Priority priority)
{
    if (!isValidTitle(task))
    {
        throw std::invalid_argument("Invalid task title");
    }

    Task new_task;
    new_task.id = last_id;
    new_task.title = task;
    new_task.completed = false;
    new_task.priority = priority;

    tasks_.push_back(new_task);
    last_id++;
}

void TaskManager::setNotifier(std::unique_ptr<Notifier> notifier)
{
    notifier_ = std::move(notifier);
}

void TaskManager::removeTask(int id)
{
    auto task = findTask(id);

    if (task == nullptr)
        return;

    std::string removedTitle = task->title;

    auto new_end = std::remove_if(tasks_.begin(), tasks_.end(),
                                  [id](const Task &target)
                                  {
                                      return target.id == id;
                                  });
    if (new_end != tasks_.end())
    {
        if (notifier_ != nullptr)
        {
            notifier_->Send(removedTitle + " has been removed");
        }
        tasks_.erase(new_end, tasks_.end());
    }
}

void TaskManager::completeTask(int id)
{
    auto task = findTask(id);

    if (task != nullptr && !task->completed)
    {
        task->completed = true;

        if (notifier_)
        {
            notifier_->Send(task->title + " has completed");
        }
    }
}

void TaskManager::printTasks() const
{
    for (const Task &i : tasks_)
    {
        std::cout << "id: " << i.id << " task: " << i.title << " completed: "
                  << i.completed << " priority: " << priorityToString(i.priority) 
                  << " deadline: " << deadlineToString(i.deadline) << std::endl;
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

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    for (const auto &task : tasks_)
    {
        file << task.id << '|' << task.title
             << '|' << task.completed << '|' << static_cast<int>(task.priority) << '\n';
    }
    file.flush();

    if (!file)
    {
        throw std::runtime_error("Failed to write file: " + filename);
    }
}

void TaskManager::loadFromFile(const std::string &filename, LoadMode mode)
{
    std::ifstream file(filename, std::ios_base::in);

    std::string id, title, completed, priority, line;
    std::vector<Task> buff;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            if (!std::getline(ss, id, '|') ||
                !std::getline(ss, title, '|') ||
                !std::getline(ss, completed, '|') ||
                !std::getline(ss, priority))
            {
                throw std::invalid_argument("Invalid file format");
            }

            if (!isIdValid(id))
            {
                throw std::invalid_argument("Invalid task ID: " + id);
            }

            const int idInt = std::stoi(id);

            if (mode == LoadMode::Replace &&
                !isIdUnique(idInt, buff, buff.size()))
            {
                throw std::invalid_argument("Duplicate task ID");
            }

            if (isValidTitle(title) != true)
            {
                throw std::invalid_argument("Task title cannot contain '|'");
            }

            if (isValidCompleted(completed) != true)
            {
                throw std::invalid_argument("Task completed must be '0' or '1'");
            }

            if (!isPriorityValid(priority))
            {
                throw std::invalid_argument("Invalid priority: " + priority);
            }

            const int priorityInt = std::stoi(priority);

            Task new_task;
            new_task.id = idInt;
            new_task.title = title;
            new_task.completed = (completed == "1" ? true : false);
            new_task.priority = static_cast<Priority>(priorityInt);
            buff.push_back(new_task);
        }
    }
    else
    {
        throw std::runtime_error("Failed to open file: " + filename);
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
            auto maxbuffit = findMaxElement(buff);

            if (it != nullptr)
            {
                auto supermax = std::max(it->id, maxbuffit->id);
                last_id = supermax + 1;
            }
            else
            {
                last_id = maxbuffit->id + 1;
            }

            for (size_t i = 0; i < buff.size(); ++i)
            {
                bool uniqueInTasks =
                    isIdUnique(buff[i].id, tasks_, tasks_.size());

                bool uniqueInBuff =
                    isIdUnique(buff[i].id, buff, i);

                if (!uniqueInTasks || !uniqueInBuff)
                {
                    buff[i].id = last_id;
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
    return !title.empty() &&
           std::find(title.begin(), title.end(), '|') == title.end();
}
bool TaskManager::isValidCompleted(const std::string &completed) const
{
    return (completed == "1" || completed == "0");
}

bool TaskManager::isIdUnique(int id, const std::vector<Task> &vec, size_t endIndex) const
{
    for (size_t i = 0; i < endIndex; ++i)
    {
        if (vec[i].id == id)
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

void TaskManager::sortTasks(SortMode mode)
{
    switch (mode)
    {
    case SortMode::Id:
    {
        auto comp = [](const Task &lhs, const Task &rhs)
        { return lhs.id < rhs.id; };
        sortTasks(comp);
        break;
    }
    case SortMode::Title:
    {
        auto comp = [](const Task &lhs, const Task &rhs)
        { return lhs.title < rhs.title; };
        sortTasks(comp);
        break;
    }
    case SortMode::Completed:
    {
        auto comp = [](const Task &lhs, const Task &rhs)
        { return lhs.completed < rhs.completed; };
        sortTasks(comp);
        break;
    }
    case SortMode::Priority:
    {
        auto comp = [](const Task &lhs, const Task &rhs)
        { return lhs.priority > rhs.priority; };
        sortTasks(comp);
        break;
    }
    case SortMode::Deadline:
    {
        auto comp = [](const Task &lhs, const Task &rhs)
        {
            if (!lhs.deadline)
                return false;

            if (!rhs.deadline)
                return true;

            return *lhs.deadline < *rhs.deadline;
        };

        sortTasks(comp);
        break;
    }
    }
}

void TaskManager::sortTasks(std::function<bool(const Task &, const Task &)> comp)
{
    std::sort(tasks_.begin(), tasks_.end(), comp);
}

bool TaskManager::isIdValid(const std::string &idStr) const
{
    size_t pos = 0;
    int id;
    try
    {
        id = std::stoi(idStr, &pos);
    }
    catch (const std::exception &e)
    {
        return false;
    }
    if (pos != idStr.size())
    {
        return false;
    }
    if (id < 0)
    {
        return false;
    }
    return true;
}

bool TaskManager::hasUniqueIds() const
{
    std::unordered_set<int> uniqueIds;
    for (const auto &p : tasks_)
    {
        const auto result = uniqueIds.insert(p.id);
        if (!result.second)
        {
            return false;
        }
    }
    return true;
}

void TaskManager::setPriority(int id, Priority priority)
{
    auto task = findTask(id);

    if (task)
    {
        task->priority = priority;
    }
}

std::string TaskManager::priorityToString(Priority priority) const
{
    switch (priority)
    {
    case Priority::High:
        return "High";
    case Priority::Medium:
        return "Medium";
    case Priority::Low:
        return "Low";
    }

    return "Unknown";
}

bool TaskManager::isPriorityValid(const std::string &priorityStr) const
{
    return priorityStr == "0" ||
           priorityStr == "1" ||
           priorityStr == "2";
}

void TaskManager::setDeadline(
    int id,
    std::chrono::system_clock::time_point deadline)
{
    auto task = findTask(id);
    if (task)
    {
        task->deadline = deadline;
    }
}

bool TaskManager::isOverdue(int id) const
{
    const auto now = std::chrono::system_clock::now();
    const auto task = findTask(id);

    if (task)
    {
        if (!task->completed &&
            task->deadline.has_value() &&
            *task->deadline < now)
        {
            return true;
        }
    }

    return false;
}

std::vector<Task> TaskManager::getOverdueTasks() const
{
    const auto now = std::chrono::system_clock::now();

    return findTasks(
        [now](const Task &task)
        {
            return !task.completed &&
                   task.deadline.has_value() &&
                   *task.deadline < now;
        });
}

std::string TaskManager::deadlineToString(
    const std::optional<std::chrono::system_clock::time_point>& deadline
) const
{
    if (!deadline)
    {
        return "None";
    }

    std::time_t time = std::chrono::system_clock::to_time_t(*deadline);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%d.%m.%Y");

    return oss.str();
}

bool Task::operator==(const Task &other) const
{
    return id == other.id &&
           title == other.title &&
           completed == other.completed &&
           priority == other.priority;
}

bool Task::operator!=(const Task &other) const
{
    return !(*this == other);
}