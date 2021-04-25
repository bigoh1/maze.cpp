//
// This file is a part of project maze.cpp.
// Created by multifrench on 04.05.2020.
//

#include "cell.hpp"

unsigned maze::details::Cell::CellSize = 50;
unsigned maze::details::Cell::BorderSize = 5;

const sf::Color maze::details::Cell::VisitedColor{126, 202, 252};       // Light blue
const sf::Color maze::details::Cell::EntryColor{231, 76, 60};           // Red
const sf::Color maze::details::Cell::ExitColor{39, 174, 96};            // Green
const sf::Color maze::details::Cell::InSolutionPathColor{57, 165, 237}; // Blue
const sf::Color maze::details::Cell::BacktrackingColor{230, 126, 34};   // Orange
const sf::Color maze::details::Cell::HeadColor{142, 68, 173};           // Magenta
const sf::Color maze::details::Cell::BackgroundColor{236, 240, 241};    // White
const sf::Color maze::details::Cell::BorderColor{44, 62, 80};           // Black

maze::details::Cell::Cell(int r, int c)
    : row{r}, col{c}
{
    leftWall.setSize(sf::Vector2f(CellSize + BorderSize, BorderSize));
    leftWall.setPosition(sf::Vector2f(row * CellSize, col * CellSize));
    leftWall.setFillColor(BorderColor);
    leftWall.rotate(90);

    rightWall.setSize(sf::Vector2f(CellSize + BorderSize, BorderSize));
    rightWall.setPosition(sf::Vector2f(row * CellSize + CellSize, col * CellSize));
    rightWall.setFillColor(BorderColor);
    rightWall.rotate(90);

    bottomWall.setSize(sf::Vector2f(CellSize + BorderSize, BorderSize));
    bottomWall.setPosition(sf::Vector2f(row * CellSize, col * CellSize + CellSize));
    bottomWall.setFillColor(BorderColor);

    topWall.setSize(sf::Vector2f(CellSize + BorderSize, BorderSize));
    topWall.setPosition(sf::Vector2f(row * CellSize, col * CellSize));
    topWall.setFillColor(BorderColor);

    cellShape.setPosition(sf::Vector2f(row * CellSize, col * CellSize));
    cellShape.setSize(sf::Vector2f(CellSize, CellSize));
    cellShape.setFillColor(BackgroundColor);
}

void maze::details::Cell::draw(sf::RenderWindow &window)
{
    update();
    window.draw(cellShape);

    if (left)
        window.draw(leftWall);
    if (right)
        window.draw(rightWall);
    if (bottom)
        window.draw(bottomWall);
    if (top)
        window.draw(topWall);
}

void maze::details::Cell::update()
{
    if (source)
        cellShape.setFillColor(EntryColor);
    else if (destination)
        cellShape.setFillColor(ExitColor);
    else if (head)
        cellShape.setFillColor(HeadColor);
    else if (inSolutionPath)
        cellShape.setFillColor(InSolutionPathColor);
    else if (backtracking)
        cellShape.setFillColor(BacktrackingColor);
    else if (visited)
        cellShape.setFillColor(VisitedColor);
    else if (left && right && top && bottom)
        cellShape.setFillColor(BorderColor);
    else
        cellShape.setFillColor(BackgroundColor);
}
