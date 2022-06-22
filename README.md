# :snake: maze.cpp
![License badge](https://img.shields.io/github/license/multifrench/maze.cpp)
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.0%20adopted-ff69b4.svg)](code_of_conduct.md)
![Made with love in Ukraine](https://madewithlove.now.sh/ua?heart=true&colorB=%23c72b1d)

maze.cpp is a visualiser for generating and solving mazes.

## :eyes: Example
![screenshot](assets/Backtracker.png)
For more see [EXAMPLES.md](EXAMPLES.md)

## :construction_worker: Building from source
Requirements
* cmake
* Boost.Program_options
* SFML

```bash
# Download the project and move into it.
$ git clone https://github.com/multifrench/maze.cpp.git && cd maze.cpp
# Create build directory.
$ mkdir build && cd build
# Build project.
$ cmake -S .. -B . && make && cd src
# Make it executable
$ chmod +x maze.cpp_run
# Run
$ ./maze.cpp_run --help
```
Or one-liner
```
git clone https://github.com/multifrench/maze.cpp.git && cd maze.cpp && mkdir build && cd build && cmake -S .. -B . && make && cd src && chmod +x maze.cpp_run 
```

## :blue_book: Documentation
See [documentation](https://multifrench.github.io/maze.cpp/)

## :busts_in_silhouette: Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## :date: Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## :octocat: Authors

* **multifrench** - *Initial work* - [github](https://github.com/multifrench)

See also the list of [contributors](contributors) who participated in this project.

## :pencil: License

This project is licensed under the GNU GPL v.3 license - see the [LICENSE](LICENSE) file for details.
