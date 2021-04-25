//
// This file is a part of project maze_solver.
// Created by multifrench on 24.05.2020.
//

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <queue>
#include <vector>

/**
 * This class is Min-heap data structure with ENQUEUE-WITH-PRIORITY operation support.
 *
 * Wrapper over std::queue.
 */
template<typename T, typename P = int>
class PriorityQueue
{
public:
    PriorityQueue() = default;

    inline void enqueue(T data, P priority)
    { queue.emplace(data, priority); }

    T dequeue();

    inline size_t size() const
    { return queue.size(); }

    inline bool empty() const
    { return queue.empty(); }

    /// @see https://stackoverflow.com/a/709161/11829849
    inline void clear()
    { Container newQueue; std::swap(queue, newQueue); }

    ~PriorityQueue() = default;
private:
    /// Stores priority as the second element in an ordered pair.
    using ItemType = std::pair<T, P>;

    /// @see PriorityQueue<T, C>::ItemType
    struct PriorityComparator {
        bool operator()(const ItemType &a, const ItemType &b) {
            return a.second > b.second;
        }
    };

    using Container = std::priority_queue<ItemType, std::vector<ItemType>, PriorityComparator>;

    Container queue;
};

template<typename T, typename P>
T PriorityQueue<T, P>::dequeue()
{
    auto returnValue = queue.top();
    queue.pop();
    return returnValue.first;
}


#endif //PRIORITY_QUEUE_HPP
