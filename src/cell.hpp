//
// This file is a part of project maze.cpp.
// Created by multifrench on 04.05.2020.
//

#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

namespace maze::details
{
/**
 * Represents cell on the 2d plane.
 *
 * Walls are represented by Boolean flags with appropriate names.
 */
struct Cell
{
    static unsigned CellSize;
    static unsigned BorderSize;

    Cell(int row, int col);
    Cell(const Cell &copy) = default;

    int row{-1}, col{-1};

    /// True, if there is a wall on a left side.
    bool left{false};

    /// True, if there is a wall on a left side.
    bool right{false};

    /// True, if there is a wall on a left side.
    bool bottom{false};

    /// True, if there is a wall on a left side.
    bool top{false};

    bool visited{false};
    bool source{false};
    bool destination{false};

    /// @see maze::solver::Solver
    bool inSolutionPath{false};

    /// @see maze::generator::BacktrackerGenerator
    bool backtracking{false};

    /// @see maze::generator::BacktrackerGenerator
    bool head{false};

    /// SFML stuff.
    void draw(sf::RenderWindow &window);
private:
    static const sf::Color VisitedColor, EntryColor, ExitColor, InSolutionPathColor, BacktrackingColor, HeadColor, BackgroundColor, BorderColor;

    sf::RectangleShape leftWall, rightWall, bottomWall, topWall;
    sf::RectangleShape cellShape;

    /// Updates Cell::cellShape color.
    void update();
};
}

#endif //CELL_HPP
