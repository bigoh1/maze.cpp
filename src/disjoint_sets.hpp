//
// This file is a part of project maze_solver.
// Created by multifrench on 23.05.2020.
//

#ifndef DISJOINT_SETS_HPP
#define DISJOINT_SETS_HPP

#include <unordered_map>

// TODO: add path compression.

/**
 * This is class that provides disjoint sets operations with union by rank and path compression.
 *
 * A disjoint-sets data structure maintains a collection S = {S1, S2, ..., Sk} of disjoint sets.
 * Each set is identified by a representative which is some member of of the set.
 * Sets are represented by rooted trees which are encoded in the Parent property map.
 */
template<typename T, typename R = unsigned int>
class DisjointSets {
public:
    /// Return the representative for the set containing element x.
    T findSet(T x);

    /// Union two sets that contain x and y.
    void unionSet(T x, T y);
private:
    std::unordered_map<T, R> rank;
    std::unordered_map<T, T> parent;
};

template<typename T, typename R>
T DisjointSets<T, R>::findSet(T x)
{
    if (parent.count(x) == 0) {
        parent.emplace(x, x);
        rank.emplace(x, 1);
    }
    else {
        if (parent[x] != x)
            parent[x] = findSet(parent[x]);
    }
    return parent[x];
}

template<typename T, typename R>
void DisjointSets<T, R>::unionSet(T x, T y)
{
    T xSet = findSet(x);
    T ySet = findSet(y);

    if (xSet == ySet) {
        return;
    }
    if (rank[xSet] < rank[ySet]) {
        parent[xSet] = ySet;
        rank[ySet] += rank[xSet];
    }
    else if (rank[xSet] > rank[ySet]) {
        parent[ySet] = xSet;
        rank[xSet] += rank[ySet];
    }
    else {
        parent[ySet] = xSet;
        rank[xSet] = rank[xSet] + 1;
    }
}
#endif //DISJOINT_SETS_HPP
