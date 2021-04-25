cmake_minimum_required(VERSION 3.16)
project(maze.cpp)

set(SOURCES main.cpp maze.hpp maze.cpp solver.hpp solver.cpp cell.hpp cell.cpp utility.hpp utility.cpp generator.hpp generator.cpp disjoint_sets.hpp priority_queue.hpp)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(Boost 1.72.0 COMPONENTS program_options REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(maze.cpp_run ${SOURCES})
endif()


target_link_libraries(maze.cpp_run sfml-graphics ${Boost_LIBRARIES})