## Maze Solver

This project contains a C++ program developed as a part of the technical challenge for Path robotics. 

### Approach

The technical challenge present various user stories that need to be solved. The approaches applied to solve the user stories are mentioned below.

- User Story 1 - The requirement is to find an empty space in a single row. This is performed by performing a linear search on a row.
    - Assumptions - The Maze is either a 1D or a 2D maze. The program is expected to return the *first* empty space in a row if multiple empty spaces exist.
- User Story 2 - The requirement is to walk through a hallway in a hallway maze. The first scenario is when a column is a hallway. The walk is performed by finding a cell from the first row that is empty and marking it as a start cell. Futhermore, walk through that column until a wall is hit. The second scenario is when a row is a hallway. The walk is performed by finding a cell from the first column that is empty and marking it as a start cell. Futhermore, walk through that row until a wall is hit.
    - Assumptions - The Maze is either a 1D or a 2D maze. A *hallway* maze that contains either a single row hallway with empty spaces or a single column hallway with empty spaces. Provided maze contains only one hallway. The program does not work on multiple hallways.
- User Story 3 - The requirement is to find a way into a rectangular room and a way out of it. The program find a path into this rectangular room and out of it by reusing the methods implemented for the previous use story. 
    - Assumptions - The Maze is a 2D maze. A *room* is a rectangular composition of cells which are empty and is atleast two cells wide. A room always has an empty cell or door outside of it and adjacent to the top left corner and another empty cell or door adjacent to a bottom right corner. The program assumses that maze has **only one** room. The program does not provide paths for multiple rooms.

### Project Structure

The project has the following structure:
- apps - This directory contains the `solver.cpp` which contains the main method. 
- include - This directory contains the `maze.hpp` header file which contains the class and function declaractions.
- src - This directory contains various .cpp files which contain function and class definitions. 
- tests - This directory contains the unit and integration tests.

### How Tos

#### Build

To build the project, the easiest approach is to execute the [`build.sh`](scripts/build.sh) script in the `scripts` directory when the current directory is the root directory. This script creates a directory named `build` under the root directory and creates all the build related files in this directory. The executable is created under the `build/bin` subdirectory. The `build.sh` can also be executed when the current directory is any other directory in the filesystem. Similar to above, the scripts creates a `build` directory. This build has only been tested on an Ubuntu 20.04 based computer. The Google Tests are executed after build is done and no additional command has to be executed.

To build, run the following commands:
```bash
cd directory/under/which/build/shall/be/performed
path/to/build.sh
```

If you are not sure that the sytem contains all the required dependencies for building this program, then run the build script with the `--prereq` flag as shown below.
```bash
cd directory/under/which/build/shall/be/performed
path/to/build.sh --prereq
```

To clean a previous build, use the `--clean` flag when running the build script.
```bash
cd directory/under/which/build/shall/be/performed
path/to/build.sh --clean
```

Expected output is below:

<details>
  <summary>Click to expand</summary>

    ```
    Clearning the previous builds.
    Building the project
    -- The CXX compiler identification is GNU 9.4.0
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- The C compiler identification is GNU 9.4.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Found Python3: /usr/bin/python3.9 (found version "3.9.18") found components: Interpreter
    -- Looking for pthread.h
    -- Looking for pthread.h - found
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
    -- Looking for pthread_create in pthreads
    -- Looking for pthread_create in pthreads - not found
    -- Looking for pthread_create in pthread
    -- Looking for pthread_create in pthread - found
    -- Found Threads: TRUE
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/ashish/build
    Scanning dependencies of target MazeSolverLib
    [  6%] Building CXX object src/CMakeFiles/MazeSolverLib.dir/grid.cpp.o
    [ 12%] Building CXX object src/CMakeFiles/MazeSolverLib.dir/graph.cpp.o
    [ 18%] Building CXX object src/CMakeFiles/MazeSolverLib.dir/utils.cpp.o
    [ 25%] Linking CXX static library libMazeSolverLib.a
    [ 25%] Built target MazeSolverLib
    Scanning dependencies of target MazeSolver
    [ 31%] Building CXX object apps/CMakeFiles/MazeSolver.dir/solver.cpp.o
    [ 37%] Linking CXX executable ../bin/MazeSolver
    [ 37%] Built target MazeSolver
    Scanning dependencies of target gtest
    [ 43%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
    [ 50%] Linking CXX static library ../../../lib/libgtest.a
    [ 50%] Built target gtest
    Scanning dependencies of target gmock
    [ 56%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
    [ 62%] Linking CXX static library ../../../lib/libgmock.a
    [ 62%] Built target gmock
    Scanning dependencies of target gmock_main
    [ 68%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
    [ 75%] Linking CXX static library ../../../lib/libgmock_main.a
    [ 75%] Built target gmock_main
    Scanning dependencies of target gtest_main
    [ 81%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
    [ 87%] Linking CXX static library ../../../lib/libgtest_main.a
    [ 87%] Built target gtest_main
    Scanning dependencies of target test_grid
    [ 93%] Building CXX object tests/CMakeFiles/test_grid.dir/test_grid.cpp.o
    [100%] Linking CXX executable ../bin/test_grid
    Run grid tests
    [==========] Running 16 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 16 tests from GridTest
    [ RUN      ] GridTest.Constructor
    [       OK ] GridTest.Constructor (0 ms)
    [ RUN      ] GridTest.Constructor2
    File does not exist : "maps/does_not_exist.txt"
    filesystem error: File does not exist.: Success
    [       OK ] GridTest.Constructor2 (0 ms)
    [ RUN      ] GridTest.Constructor3
    File does not exist : ""
    filesystem error: File does not exist.: Success
    [       OK ] GridTest.Constructor3 (0 ms)
    [ RUN      ] GridTest.Constructor4
    [       OK ] GridTest.Constructor4 (0 ms)
    [ RUN      ] GridTest.Constructor5
    [       OK ] GridTest.Constructor5 (0 ms)
    [ RUN      ] GridTest.SearchARowForEmptySpace1
    [       OK ] GridTest.SearchARowForEmptySpace1 (0 ms)
    [ RUN      ] GridTest.SearchARowForEmptySpace2
    [       OK ] GridTest.SearchARowForEmptySpace2 (0 ms)
    [ RUN      ] GridTest.SearchARowForEmptySpace3
    Row index is out of bounds.
    [       OK ] GridTest.SearchARowForEmptySpace3 (0 ms)
    [ RUN      ] GridTest.SearchARowForEmptySpace4
    [       OK ] GridTest.SearchARowForEmptySpace4 (0 ms)
    [ RUN      ] GridTest.SearchARowForEmptySpace5
    Invalid map file : "maps/multiple_rows_2.txt"
    Invalid map file.
    [       OK ] GridTest.SearchARowForEmptySpace5 (0 ms)
    [ RUN      ] GridTest.HallwayWalk1
    [       OK ] GridTest.HallwayWalk1 (0 ms)
    [ RUN      ] GridTest.HallwayWalk2
    [       OK ] GridTest.HallwayWalk2 (0 ms)
    [ RUN      ] GridTest.HallwayWalk3
    [       OK ] GridTest.HallwayWalk3 (0 ms)
    [ RUN      ] GridTest.HallwayWalk4
    [       OK ] GridTest.HallwayWalk4 (0 ms)
    [ RUN      ] GridTest.HallwayWalk5
    [       OK ] GridTest.HallwayWalk5 (0 ms)
    [ RUN      ] GridTest.HallwayWalk6
    [       OK ] GridTest.HallwayWalk6 (0 ms)
    [----------] 16 tests from GridTest (0 ms total)

    [----------] Global test environment tear-down
    [==========] 16 tests from 1 test suite ran. (0 ms total)
    [  PASSED  ] 16 tests.
    [100%] Built target test_grid
    /home/ashish
    Build complete
    ```
</details>


#### Execution

To run the program, prepare a file that encodes a maze has to be created. Creating a text file that encodes a maze using 1s and 0s involves the below steps.
- Design maze layout - First create a layout of a MxN grid, where M is the number of rows and N is the number of columns. Plan the pathways and walls. Pathways must be represented by '0's (indicating free space) and walls by '1's (indicating blocked space).
- Text Editor - Open a text editor on your computer. Avoid using word processors, as they add additional formatting that can interfere with the maze structure.
- Encode the Maze: Start encoding the maze into the text file. Begin from the top-left corner of your maze design, translating each cell into a '1' for a wall or a '0' for a path. Enter the corresponding number for each cell in your maze grid, moving from left to right. Please **do not** use spaces or any other characters.
- Use Line Breaks for Rows: At the end of each row of the maze, press 'Enter' to start a new line. This will ensure that each row of your maze is on a separate line in the text file, maintaining the grid structure. Ensure that the number of columns are consistent. This program only accepts a MxN grid.
- Save the File: Once you've finished encoding the entire maze, save the file. Choose a suitable file name and ensure it has a '.txt' extension. For example, you might name it `maze.txt`.

After the maze has been created, run the solver using the following commands:
```bash
cd to/directory/under/which/build/was/performed
./build/bin/MazeSolver -m path/to/maze/file <options>
```

The `MazeSolver` executable requires path to the maze file. Optionally, a user story id can also be provided to the program. If user story id is not provided, the program will default to the highest user story implement in the last commit. Expected output for different user stories are shown below:


- User Story 1
```
./build/bin/MazeSolver -m path/to/maze/file -u 1
First empty space in row 1 is at column 2
```

- User Story 2
```
./build/bin/MazeSolver -m path/to/maze/file -u 2
Path Start -> (0, 3) -> (1, 3) -> (2, 3) -> (3, 3) -> (4, 3) -> (5, 3) -> End
```

- User Story 3
```
./build/bin/MazeSolver -m path/to/maze/file # or -u 3
Path Start -> (0, 1) -> (1, 1) -> (2, 1) -> (2, 2) -> (2, 3) -> (2, 4) -> (3, 4) -> End
```

### License
This program is licensed under GPL 3, license [here](LICENSE.md).