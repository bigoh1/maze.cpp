//
// This file is a part of project maze.cpp.
// Created by multifrench on 03.05.2020.
//

#include "solver.hpp"

maze::solver::Solver::CellPtr maze::solver::DFSSolver::extractNext()
{
    auto returnValue = container.top();
    container.pop();
    return returnValue;
}

maze::solver::Solver::CellPtr maze::solver::BFSSolver::extractNext()
{
    auto returnValue = container.front();
    container.pop();
    return returnValue;
}

void maze::solver::AStarSolver::solve(maze::Maze &maze)
{
    /// TODO: reduce duplicated code!
    /// Reached the source vertex.
    if (maze.solved && currPaint == maze.source()) {
        maze.painted = true;
    }
    /// If maze is solved and solution path in maze is still unpainted, paint it.
    if (maze.solved && !maze.painted) {
        if (currPaint != nullptr)
            currPaint = details::PaintSolutionPath(maze, parent, currPaint);
    }
    else if (!maze.source()->visited) {
        gCost[maze.source()] = 0.0;
        fCost[maze.source()] = details::Distance(maze.source(), maze.destination());

        queue.enqueue(maze.source(), fCost[maze.source()]);
        maze.source()->visited = true;
        parent[maze.source()] = nullptr;
    }
    /// Exploring maze.
    else if (!queue.empty() && !pathFound) {
        auto top = queue.dequeue();
        top->visited = true;

        /// If reached the destination, exit.
        if (top == maze.destination()) {
            pathFound = true;
            return;
        }

        for (auto &n : details::AccessibleUnvisitedNeighbors(top, maze)) {
            /// Increment by 1.0, because weight of each non-diagonal edge in a 2d grid is 1.
            auto tentative_gCost = gCost[top] + 1.0;

            /// Do relaxation.
            //  gCost[n] == INF ...
            if (gCost.count(n) == 0 || tentative_gCost < gCost[n]) {
                parent[n] = top;
                gCost[n] = tentative_gCost;
                fCost[n] = gCost[n] + details::Distance(n, maze.destination());

                queue.enqueue(n, fCost[n]);
            }
        }
    }
    /// If path is found, start painting maze.
    else if (pathFound) {
        currPaint = maze.destination();
        maze.solved = true;
    }
    /// There is no path from maze.source() to maze.destination().
    else if (!queue.empty() && !maze.solved) {
        throw PathNotFoundException{};
    }
}

void maze::solver::Update(Maze &maze, std::shared_ptr<solver::Solver> sol, sf::RenderWindow &window)
{
    if (maze.generated) {
        sol->solve(maze);
        maze.display(window);
    }
}
