//
// This file is a part of project maze.cpp.
// Created by multifrench on 09.05.2020.
//

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "cell.hpp"
#include "maze.hpp"

#include <cmath>

#include <random>
#include <vector>
#include <unordered_map>

/// Implementation details.
namespace maze::details
{
struct Coord {
    int x, y;
};

/// Returns True, if there is a wall between a and b.
bool IsWallBetween(maze::Maze::CellPtr a, maze::Maze::CellPtr b);

/// Removes wall between cells a and b.
void RemoveWallBetween(maze::Maze::CellPtr a, maze::Maze::CellPtr b);

/// Calculates euclidean distance between cells a and b assuming that the length from one cell to it's neighbors is 1.
double Distance(Maze::CellPtr a, Maze::CellPtr b);

/**
 * Clears specified Cell flags.
 *
 * @see Cell::visited
 * @see Cell::inSolutionPath
 * @see Cell::backtracking
 *
 * @see Cell::left
 * @see Cell::right
 * @see Cell::bottom
 * @see Cell::top
 */
void ClearCellFlags(Maze &maze, bool visited = true, bool inSolutionPath = false, bool backtracking = false, bool setWalls = false);

/// For each cell in the path (from maze.source() to maze.destination()), sets flag inTheSolutionPath to true.
Maze::CellPtr PaintSolutionPath(Maze &maze, const std::unordered_map<Maze::CellPtr, Maze::CellPtr> &parent, Maze::CellPtr currPaint);

/// Returns all possible neighbors of cell c. At most 4.
std::vector<maze::Maze::CellPtr> Neighbors(maze::Maze::CellPtr c, Maze &maze);

/// Returns unvisited neighbors of cell c.
std::vector<maze::Maze::CellPtr> UnvisitedNeighbors(maze::Maze::CellPtr c, Maze &maze);

/// Returns unvisited neighbors of cell c such that there is no wall between a particular neighbor and the cell.
std::vector<maze::Maze::CellPtr> AccessibleUnvisitedNeighbors(maze::Maze::CellPtr c, Maze &maze);

/// Generates random integer ∈ [a; b].
size_t GetRandomInteger(size_t a, size_t b);

/**
 * Chooses a random value from A and returns it.
 *
 * @param A is a vector, because this function uses random access to be O(1).
 * @relatesalso GetRandomInteger()
 * @returns random item ∈ A[0..n-1].
 */
template<typename T>
T RandomChoice(std::vector<T> &A);

/**
 * Chooses a random value from A, erases it from the container and returns.
 *
 * @param A can be any container that supports iterating.
 * @relatesalso GetRandomInteger()
 * @returns random item ∈ A[0..n-1].
 */
template<typename C, typename T>
T RandomChoiceAndErase(C &A);
}

template<typename T>
T maze::details::RandomChoice(std::vector<T> &A)
{
    auto randomIndex = GetRandomInteger(0, A.size() - 1);
    return A[randomIndex];
}

template<typename C, typename T>
T maze::details::RandomChoiceAndErase(C &A)
{
    auto randomIndex = GetRandomInteger(0, A.size() - 1);

    auto it = A.begin();
    for (auto counter = 0; counter < randomIndex; ++counter)
        ++it;

    auto returnValue = *it;
    A.erase(it);

    return returnValue;
}

namespace std
{
template<>
struct hash<maze::Maze::EdgePtr>
{
    std::size_t operator()(const maze::Maze::EdgePtr &k) const
    {
        using std::hash;
        hash<maze::Maze::CellPtr> hCellPtr;

        return hCellPtr(k.first) ^ hCellPtr(k.second);
    }
};
}

#endif //UTILITY_HPP
