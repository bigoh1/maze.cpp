//
// This file is a part of project maze.cpp.
// Created by multifrench on 09.05.2020.
//

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "disjoint_sets.hpp"
#include "utility.hpp"
#include "maze.hpp"

#include <SFML/Graphics.hpp>

#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>
#include <unordered_set>

namespace maze::generator
{
/**
 * This class provides generation functional for maze puzzle.
 *
 * @see maze::Maze
 */
class Generator
{
public:
    /**
     * Generates maze.
     *
     * @param maze All wall flags must be set.
     */
    virtual void generate(Maze &maze) = 0;

    /**
    * Clears data was used to generate a maze.
    *
    * Must be called before regeneration of the maze. The function relies on constructor.
    * @see https://stackoverflow.com/a/709161/11829849
    * @code{.cpp}
    * maze::generator::Generator empty;
    * std::swap(*this, empty);
    * @endcode
    */
    inline virtual void clear() = 0;

    virtual ~Generator() = default;
};

/**
 * Recursive backtracker algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Maze_generation_algorithm#Recursive_backtracker
 */
class BacktrackerGenerator final : public Generator
{
public:
    void generate(Maze &maze) override;
    inline void clear() override
    { BacktrackerGenerator empty; std::swap(*this, empty); }

    ~BacktrackerGenerator() override = default;
private:
    std::stack<Maze::CellPtr> cellsStack;
    Maze::CellPtr prevCell{nullptr};

    bool generationStarted{false};
};

/**
 * Randomized Kruskal's algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_Kruskal's_algorithm
 */
class KruskalsGenerator final : public Generator
{
public:
    void generate(Maze &maze) override;
    inline void clear() override
    { KruskalsGenerator empty; std::swap(*this, empty); }

    ~KruskalsGenerator() override = default;
private:
    DisjointSets<Maze::CellPtr> ds;
    std::unordered_set<Maze::EdgePtr> edges;

    bool generationStarted{false};
};

/**
 * Randomized Prim's algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_Prim's_algorithm
 */
class PrimsGenerator final : public Generator
{
public:
    void generate(Maze &maze) override;
    inline void clear() override
    { PrimsGenerator empty; std::swap(*this, empty); }

    ~PrimsGenerator() override = default;
private:
    std::unordered_set<Maze::EdgePtr> walls;

    bool generationStarted{false};
};

void Update(Maze &maze, std::shared_ptr<Generator> gen, sf::RenderWindow &window);
}

#endif //GENERATOR_HPP
