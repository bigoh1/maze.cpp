//
// This file is a part of project maze.cpp.
// Created by multifrench on 03.05.2020.
//

#ifndef MAZE_HPP
#define MAZE_HPP

#include "cell.hpp"

#include <vector>
#include <memory>
#include <utility>

namespace maze
{
/// Represents maze puzzle.
class Maze
{
public:
    using Cell = details::Cell;
    using CellPtr = std::shared_ptr<Cell>;
    using EdgePtr = std::pair<CellPtr, CellPtr>;

    using GridContainer = std::vector<CellPtr>;

    Maze(unsigned width, unsigned height, bool walls = true);
    Maze(const Maze &copy);

    Maze(Maze &&move);

    inline CellPtr at(int row, int col)
    { return grid.at(getIndex(row, col)); }

    inline bool check(int row, int col) const noexcept
    { return 0 <= row && row < rowNum() && 0 <= col && col < colNum();}

    inline unsigned colNum() const noexcept
    { return columns; }
    inline unsigned rowNum() const noexcept
    { return rows; }

    inline unsigned cellsNum() const noexcept
    { return colNum() * rowNum(); }

    inline CellPtr source() const noexcept
    { return begin; }
    inline CellPtr destination() const noexcept
    { return end; }

    void setSource(CellPtr);
    void setDestination(CellPtr);

    /// SFML stuff.
    void display(sf::RenderWindow &window);

    bool generated{false}, solved{false}, painted{false};
private:
    /**
     * Maps a 2D into a 1D array.
     * @see https://stackoverflow.com/a/2151141/11829849
     */
    inline int getIndex(int row, int col) const noexcept
    { return colNum() * row + col; }

    unsigned columns{}, rows{};
    CellPtr begin{nullptr}, end{nullptr};

    GridContainer grid;

    void initGrid(bool walls);
};
}

#endif //MAZE_HPP
