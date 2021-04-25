//
// This file is a part of project maze.cpp.
// Created by multifrench on 03.05.2020.
//

#ifndef MAZE_SOLVER_HPP
#define MAZE_SOLVER_HPP

#include "cell.hpp"
#include "maze.hpp"
#include "priority_queue.hpp"

#include "utility.hpp"

#include <queue>
#include <stack>
#include <unordered_map>

namespace maze::solver
{
// TODO: catch PathNotFoundException
class PathNotFoundException : public std::runtime_error {
public:
    PathNotFoundException() : std::runtime_error{"Path not found."} {}
};

/**
 * This class provides solving functional for maze puzzle.
 *
 * @see maze::Maze
 */
class Solver
{
public:
    using CellPtr = Maze::CellPtr;

    /**
     * Finds path from maze.source() to maze.destination(). For each cell in the path, sets flag inSolutionPath to true.
     *
     * @result Sets flag Cell::inSolutionPath of each cell in the found solution path.
     * @see Cell::inSolutionPath
     * @see maze::details::PaintSolutionPath()
     * @throws maze::solver::PathNotFoundException
     */
    virtual void solve(Maze &maze) = 0;

    /**
     * Clears data was used to solve a maze.
     *
     * Must be called before resolving a maze. The function relies on constructor.
     * @see https://stackoverflow.com/a/709161/11829849
     * @code{.cpp}
     * maze::solver::Solver empty;
     * std::swap(*this, empty);
     * @endcode
     */
    virtual void clear() = 0;

    virtual ~Solver() = default;
};

/// Iterative versions of DFS and BFS differs only in data structure used (stack/queue).
template<typename C>
class BFSandDFSBase : public Solver {
public:
    void solve(Maze &maze) override;

    virtual ~BFSandDFSBase() = default;
protected:
    C container;
private:
    /// Must return next element of the container and pop it.
    virtual CellPtr extractNext() = 0;

    std::unordered_map<CellPtr, CellPtr> parent;

    CellPtr currPaint{nullptr};
    bool pathFound{false};
};

/**
 * Depth-first search algorithm
 *
 * Finds ANY path from source to destination.
 * Takes O(V + E) time.
 */
class DFSSolver final : public BFSandDFSBase<std::stack<Maze::CellPtr>>
{
public:
    inline void clear() override
    { DFSSolver empty; std::swap(*this, empty); }

    ~DFSSolver() override = default;
private:
    CellPtr extractNext() override;
};

/**
 * Breadth-first search algorithm
 *
 * Finds SHORTEST path from source to destination.
 * Takes O(V + E) time.
 */
class BFSSolver final : public BFSandDFSBase<std::queue<Maze::CellPtr>>
{
public:
    inline void clear() override
    { BFSSolver empty; std::swap(*this, empty); }

    ~BFSSolver() override = default;
private:
    CellPtr extractNext() override;
};

/**
 * A*
 *
 * Finds SHORTEST path from source to destination in OPTIMAL time.
 * Takes O(E) time.
 */
class AStarSolver final : public Solver
{
public:
    void solve(Maze &maze) override;
    inline void clear() override
    { AStarSolver empty; std::swap(*this, empty); }

    ~AStarSolver() override = default;
private:
    std::unordered_map<Maze::CellPtr, Maze::CellPtr> parent;
    PriorityQueue<Maze::CellPtr> queue;
    std::unordered_map<CellPtr, double> fCost, gCost;

    Maze::CellPtr currPaint{nullptr};
    bool pathFound{false};
};

void Update(Maze &maze, std::shared_ptr<Solver> sol, sf::RenderWindow &window);
}

template<typename C>
void maze::solver::BFSandDFSBase<C>::solve(Maze &maze)
{
    // Reached the source vertex.
    if (maze.solved && currPaint == maze.source()) {
        maze.painted = true;
    }
    // If maze is solved and solution path in maze is still unpainted, paint it.
    if (maze.solved && !maze.painted) {
        currPaint = details::PaintSolutionPath(maze, parent, currPaint);
    }
    // Add source vertex to the stack/queue.
    else if (!maze.source()->visited) {
        parent[maze.source()] = nullptr;
        container.push(maze.source());
        maze.source()->visited = true;
    }
    // Exploring maze.
    else if (!container.empty() && !pathFound) {
        auto top = extractNext();
        top->visited = true;

        // If reached the destination, exit.
        if (top == maze.destination()) {
            pathFound = true;
            return;
        }

        // Add unvisited neighbors of top to the stack/queue.
        for (auto &n : details::AccessibleUnvisitedNeighbors(top, maze)) {
            parent[n] = top;
            container.push(n);
        }
    }
    // If path is found, start painting maze.
    else if (pathFound) {
        currPaint = maze.destination();
        maze.solved = true;
    }
    // There is no path from maze.source() to maze.destination().
    else if (!container.empty() && !maze.solved) {
        throw PathNotFoundException{};
    }
}

#endif //MAZE_SOLVER_HPP
