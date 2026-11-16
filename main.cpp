#include "TaskManager.h"

#include <cassert>
#include <iostream>
#include <algorithm>

#include "TaskManager.h"
#include "Notifier.h"

#include <iostream>

template <typename T, typename U>
bool contains(const std::vector<T> &items, const U &value)
{
    return std::any_of(
        items.begin(),
        items.end(),
        [&value](const T &item)
        {
            return item == value;
        });
}

template <typename T, typename Predicate>
const T *findFirst(const std::vector<T> &items, Predicate predicate)
{
    const auto it = std::find_if(items.begin(), items.end(), predicate);
    if (it != items.end())
    {
        return &(*it);
    }
    return nullptr;
}

template <typename T, typename Predicate>
std::vector<const T *> findAll(
    const std::vector<T> &items,
    Predicate predicate)
{
    std::vector<const T *> result;

    auto it = items.begin();

    while (it != items.end())
    {
        auto res_it = std::find_if(it, items.end(), predicate);

        if (res_it == items.end())
        {
            break;
        }

        result.push_back(&(*res_it));
        it = std::next(res_it);
    }

    return result;
}

int main()
{
    std::vector<int> numbers;

    for (int i = 0; i < 10; ++i)
    {
        numbers.push_back(i);

        std::cout << "size: " << numbers.size()
                  << " capacity: " << numbers.capacity()
                  << " address: " << numbers.data()
                  << '\n';
    }
    return 0;
}