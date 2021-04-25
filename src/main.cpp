#include "maze.hpp"
#include "generator.hpp"
#include "solver.hpp"

#include <SFML/Graphics.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <string>
#include <memory>

using namespace maze;
using namespace generator;
using namespace solver;
using namespace details;

namespace po = boost::program_options;

void Update(Maze &maze, std::shared_ptr<Generator> gen, std::shared_ptr<Solver> sol, sf::RenderWindow &window, bool &startSolving, bool &startGeneration);

int main(int argc, char *argv[])
{
    unsigned columns, rows, width, height;

    std::shared_ptr<Generator> generator;
    std::shared_ptr<Solver> solver;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produces help message")
        ("generation,G", po::value<std::string>()->default_value("Backtracker"), "set generation algorithm. List of such: Backtracker, Kruskal's, Prim's")
        ("solving,S", po::value<std::string>()->default_value("A*"), "set solving algorithm. List of such: DFS, BFS, A*")
        ("columns,C", po::value<unsigned>(&columns), "set number of columns")
        ("rows,R", po::value<unsigned>(&rows), "set number of rows")
        ("cell-size", po::value<unsigned>(&maze::details::Cell::CellSize), "set size of cells (in px)")
        ("border-size", po::value<unsigned>(&maze::details::Cell::BorderSize), "set size of borders (in px)")
        ("antialiasing", po::value<unsigned>()->default_value(4), "set antialiasing level. Values are non-negative integers")
        ("FPS", po::value<unsigned>()->default_value(60), "set framerate limit");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }

    // Determine generation algorithm.
    if (vm["generation"].as<std::string>() == "Backtracker") {
        generator = std::make_shared<BacktrackerGenerator>();
    }
    else if (vm["generation"].as<std::string>() == "Kruskal's") {
        generator = std::make_shared<KruskalsGenerator>();
    }
    else if (vm["generation"].as<std::string>() == "Prim's") {
        generator = std::make_shared<PrimsGenerator>();
    }
    else {
        std::cerr << "Incorrect generation algorithm '" << vm["generation"].as<std::string>() << "'." << std::endl
                  << "Run --help to see the list of generation algorithms." << std::endl;
        return EXIT_FAILURE;
    }

    // Determine solving algorithm.
    if (vm["solving"].as<std::string>() == "DFS") {
        solver = std::make_shared<DFSSolver>();
    }
    else if (vm["solving"].as<std::string>() == "BFS") {
        solver = std::make_shared<BFSSolver>();
    }
    else if (vm["solving"].as<std::string>() == "A*") {
        solver = std::make_shared<AStarSolver>();
    }
    else {
        std::cerr << "Incorrect solving algorithm '" << vm["solving"].as<std::string>() << "'." << std::endl
                  << "Run --help to see the list of solving algorithms." << std::endl;
        return EXIT_FAILURE;
    }

    // TODO: FIX-ME.
    // Calculate maximum number of columns and rows that is possible to fit on the screen.
    if (vm.count("columns") == 0) {
        columns = sf::VideoMode::getDesktopMode().width / Cell::CellSize;
    }
    if (vm.count("rows") == 0) {
        rows = sf::VideoMode::getDesktopMode().height / (Cell::CellSize + 2);
    }

    // Calculate width and height of the window.
    width = details::Cell::CellSize * columns;
    height = details::Cell::CellSize * rows;

    // Check whether the window size fits the screen or not.
    if (width > sf::VideoMode::getDesktopMode().width || height > sf::VideoMode::getDesktopMode().height) {
        std::cerr << "Maze of size " << columns << " x " << rows << " is too big for a "
                  << sf::VideoMode::getDesktopMode().width << " x " << sf::VideoMode::getDesktopMode().height <<  " monitor."
                  << "You may leave --columns[-C] and/or --rows[-R] options to set appropriate values to maximum." << std::endl;
        return EXIT_FAILURE;
    }

    sf::ContextSettings settings;
    // Set antialiasing level.
    settings.antialiasingLevel = vm["antialiasing"].as<unsigned>();

    sf::RenderWindow window{sf::VideoMode{width, height}, "maze.cpp", sf::Style::Default, settings};
    // Set framerate limit.
    window.setFramerateLimit(vm["FPS"].as<unsigned>());

    Maze maze{columns, rows};
    bool startSolving{true}, startGenerating{true};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // If Escape is pressed, generate and solve a new one maze.
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                // TODO: add Maze::clear() function.
                maze.generated = false;
                maze.solved = false;
                maze.painted = false;

                startGenerating = true;
                startSolving = true;

                details::ClearCellFlags(maze, true, true, true, true);

                generator->clear();
                solver->clear();
            }
        }

        window.clear(sf::Color::White);
        Update(maze, generator, solver, window, startSolving, startGenerating);
        window.display();
    }

    return EXIT_SUCCESS;
}

void Update(Maze &maze, std::shared_ptr<Generator> gen, std::shared_ptr<Solver> sol, sf::RenderWindow &window, bool &startSolving, bool &startGeneration)
{
    if (startGeneration) {
        if (maze.generated)
            startGeneration = false;
        Update(maze, gen, window);
    }
    if (startSolving) {
        if (maze.painted)
            startSolving = false;
        Update(maze, sol, window);
    }
    maze.display(window);
}

