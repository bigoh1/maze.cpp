//
// This file is a part of project maze.cpp.
// Created by multifrench on 09.05.2020.
//

#include "utility.hpp"

std::vector<maze::Maze::CellPtr> maze::details::Neighbors(Maze::CellPtr c, Maze &maze)
{
    std::vector<Maze::CellPtr> output;
    int x = c->row, y = c->col;

    Coord left{x - 1, y}, right{x + 1, y}, up{x, y - 1}, down{x, y + 1};

    if (maze.check(left.x, left.y))
        output.push_back(maze.at(left.x, left.y));
    if (maze.check(right.x, right.y))
        output.push_back(maze.at(right.x, right.y));
    if (maze.check(up.x, up.y))
        output.push_back(maze.at(up.x, up.y));
    if (maze.check(down.x, down.y))
        output.push_back(maze.at(down.x, down.y));

    return output;
}

std::vector<maze::Maze::CellPtr> maze::details::UnvisitedNeighbors(maze::Maze::CellPtr c, maze::Maze &maze)
{
    auto neighbors = Neighbors(c, maze);
    std::vector<maze::Maze::CellPtr> output;

    if (neighbors.empty())
        return neighbors;
    for (const auto &item : neighbors)
        if (!item->visited)
            output.push_back(item);
    return output;
}

std::vector<maze::Maze::CellPtr> maze::details::AccessibleUnvisitedNeighbors(maze::Maze::CellPtr c, maze::Maze &maze)
{
    auto neighbors = UnvisitedNeighbors(c, maze);
    std::vector<maze::Maze::CellPtr> output;

    if (neighbors.empty()) return neighbors;

    for (const auto &item : neighbors)
        if (!IsWallBetween(item, c))
            output.push_back(item);
    return output;
}

bool maze::details::IsWallBetween(maze::Maze::CellPtr a, maze::Maze::CellPtr b)
{
    if (a->row - b->row == -1 && a->right && b->left)
        return true;
    if (a->row - b->row == 1 && a->left && b->right)
        return true;
    if (a->col - b->col == -1 && a->bottom && b->top)
        return true;
    if (a->col - b->col == 1 && a->top && b->bottom)
        return true;
    return false;
}



void maze::details::RemoveWallBetween(maze::Maze::CellPtr a, maze::Maze::CellPtr b)
{
    if (a->row - b->row == -1) {
        a->right = b->left = false;
    }
    else if (a->row - b->row == 1) {
        a->left = b->right = false;
    }
    else if (a->col - b->col == -1) {
        a->bottom = b->top = false;
    }
    else if (a->col - b->col == 1) {
        a->top = b->bottom = false;
    }
}

void maze::details::ClearCellFlags(maze::Maze &maze, bool visited, bool inSolutionPath, bool backtracking, bool setWalls)
{
    for (auto row = 0; row < maze.rowNum(); ++row) {
        for (auto col = 0; col < maze.colNum(); ++col) {
            auto cell = maze.at(row, col);
            if (visited)
                cell->visited = false;
            if (inSolutionPath)
                cell->inSolutionPath = false;
            if (backtracking)
                cell->backtracking = cell->head = false;
            if (setWalls)
                cell->left = cell->right = cell->top = cell->bottom = true;
        }
    }
}


size_t maze::details::GetRandomInteger(size_t a, size_t b)
{
    static std::random_device rd;
    static std::mt19937 random_engine(rd());
    std::uniform_int_distribution<size_t> u{a, b};

    return u(rd);
}

maze::Maze::CellPtr maze::details::PaintSolutionPath(maze::Maze &maze, const std::unordered_map<Maze::CellPtr, Maze::CellPtr> &parent, Maze::CellPtr currPaint)
{
    if (currPaint != nullptr)
        currPaint->inSolutionPath = true;
    return parent.at(currPaint);
}

double maze::details::Distance(maze::Maze::CellPtr a, maze::Maze::CellPtr b)
{
    /// d(a, b) = √((a.x - b.x)^2 + (a.y - b.y)^2)
    return sqrt(pow(a->row - b->row, 2) + pow(a->col - b->col, 2));
}