//
// This file is a part of project maze.cpp.
// Created by multifrench on 09.05.2020.
//

#include "generator.hpp"

// TODO: comment generation code.
void maze::generator::BacktrackerGenerator::generate(Maze &maze)
{
    if (!maze.generated && !generationStarted) {
        cellsStack.push(maze.source());
        maze.source()->visited = true;

        prevCell = maze.source();
        generationStarted = true;
    }
    else if (!maze.generated && !cellsStack.empty() && generationStarted) {
        auto top = cellsStack.top();
        prevCell->head = false;
        top->head = true;
        top->visited = true;

        cellsStack.pop();

        auto neighbors = details::UnvisitedNeighbors(top, maze);
        if (!neighbors.empty()) {
            cellsStack.push(top);
            auto s = details::RandomChoice(neighbors);

            details::RemoveWallBetween(top, s);
            cellsStack.push(s);
        }
        else {
            top->backtracking = true;
        }

        prevCell = top;
    }
    else if (cellsStack.empty() && generationStarted) {
        maze.generated = true;
        details::ClearCellFlags(maze, true, false, true);
    }
}
void maze::generator::KruskalsGenerator::generate(Maze &maze)
{
    if (!maze.generated && edges.empty() && !generationStarted) {
        generationStarted = true;

        for (auto x = 0; x < maze.rowNum(); ++x) {
            for (auto y = 0; y < maze.colNum(); ++y) {
                if (maze.check(x + 1, y)) {
                    edges.emplace(maze.at(x, y), maze.at(x + 1, y));
                }
                if (maze.check(x, y + 1)) {
                    edges.emplace(maze.at(x, y), maze.at(x, y + 1));
                }
            }
        }
    }
    else if (!edges.empty()) {
        auto edge = details::RandomChoiceAndErase<std::unordered_set<Maze::EdgePtr>, Maze::EdgePtr>(edges);
        if (ds.findSet(edge.first) != ds.findSet(edge.second)) {
            details::RemoveWallBetween(edge.first, edge.second);
            ds.unionSet(edge.first, edge.second);
        }
    }
    else if (edges.empty() && generationStarted) {
        maze.generated = true;
        details::ClearCellFlags(maze);
    }
}

void maze::generator::PrimsGenerator::generate(Maze &maze)
{
    if (!maze.generated && walls.empty() && !generationStarted) {
        generationStarted = true;

        for (auto &n : details::Neighbors(maze.source(), maze)) {
            if (details::IsWallBetween(maze.source(), n))
                walls.emplace(maze.source(), n);
        }
    }
    else if (!walls.empty() && generationStarted) {
        auto top = details::RandomChoiceAndErase<std::unordered_set<Maze::EdgePtr>, Maze::EdgePtr>(walls);
        top.first->visited = true;

        if (top.first->visited && !top.second->visited) {
            details::RemoveWallBetween(top.first, top.second);
            for (auto &n : details::Neighbors(top.second, maze)) {
                if (details::IsWallBetween(top.second, n))
                    walls.emplace(top.second, n);
            }
        }
        else if (!top.first->visited && top.second->visited) {
            details::RemoveWallBetween(top.first, top.second);
            for (auto &n : details::Neighbors(top.first, maze)) {
                if (details::IsWallBetween(top.first, n))
                    walls.emplace(top.first, n);
            }
        }
    }
    else if (walls.empty() && generationStarted) {
        maze.generated = true;
        details::ClearCellFlags(maze);
    }
}

void maze::generator::Update(Maze &maze, std::shared_ptr<Generator> gen, sf::RenderWindow &window)
{
    if (!maze.generated) {
        gen->generate(maze);
        maze.display(window);
    }
}
