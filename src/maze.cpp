//
// This file is a part of project maze.cpp.
// Created by multifrench on 03.05.2020.
//

#include "maze.hpp"

/// TODO: deal with col and row, they are not appropriate.
maze::Maze::Maze(unsigned width, unsigned height, bool walls)
    : columns{height}, rows{width}
{
    initGrid(walls);
}

void maze::Maze::display(sf::RenderWindow &window)
{
    for (const auto &cell : grid)
        cell->draw(window);
}

void maze::Maze::initGrid(bool walls)
{
    /// Fill grid.
    for (int x = 0; x < rowNum(); ++x) {
        for (int y = 0; y < colNum(); ++y) {
            auto cell = std::make_shared<Cell>(x, y);

            cell->left = cell->right = cell->bottom = cell->top = walls;
            grid.push_back(std::move(cell));
        }
    }

    /// Set source and destination points.
    begin = at(0, 0);
    end = at(rowNum() - 1, colNum() - 1);

    setSource(begin);
    setDestination(end);
}

maze::Maze::Maze(const maze::Maze &copy)
{
    columns = copy.columns;
    rows = copy.rows;

    for (const auto &item : copy.grid)
        grid.push_back(std::make_shared<Cell>(*item));

    begin = at(copy.begin->row, copy.begin->col);
    end = at(copy.end->row, copy.end->col);
}

void maze::Maze::setSource(CellPtr src) {
    source()->source = false;

    begin = src;
    begin->source = true;
}

void maze::Maze::setDestination(CellPtr dst)
{
    destination()->destination = false;

    end = dst;
    end->destination = true;
}

maze::Maze::Maze(maze::Maze &&move)
{
    /// TODO: reduce duplicated code [Maze::Maze(const Maze &copy)]
    columns = move.columns;
    rows = move.rows;

    std::swap(grid, move.grid);

    begin = at(move.begin->row, move.begin->col);
    end = at(move.end->row, move.end->col);
}
