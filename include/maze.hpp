// Copyright (C) 2023 Ashish Kumar
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program in the file: gpl-3.0.text. 
// If not, see <http://www.gnu.org/licenses/>.

#ifndef MAZE_H 
#define MAZE_H

// stl includes
#include <cstddef>
#include <vector>
#include <filesystem>

namespace maze
{
    namespace grid
    {   
        // readMap function that reads the map file and returns
        // a 2D vector of integers
        std::vector<std::vector<int>> readMap(std::filesystem::path const& filepath);

        // Constants class that holds all the constants
        // These constants are used across the project
        class Constants
        {
            public:
                static constexpr int INDEX_NOT_FOUND = -1;
        };

        // Grid class that holds the grid map and provides
        // methods to access the grid map. Additionally, it
        // provides methods to search the grid map.
        class Grid
        {
            public:
                Grid(std::string const& map_file_path);
                ~Grid();

                const std::vector<std::vector<int>>& getGridMap() const;

                // initializeGridMap function that initializes the grid map
                // from the map file
                void initializeGridMap(std::string const& map_file_path);

                // searchARowForEmptySpace function that searches
                // a row of the grid map for empty space
                int searchARowForEmptySpace(const int row_index) const;

                // isInitialized function that returns true if the grid map
                // is initialized, false otherwise
                const bool& isInitialized() const;

                // walkThrouhHallway function that returns a vector of pairs
                // of integers. Each pair represents a cell in the grid map
                // that is part of the hallway
                std::vector<std::pair<int, int>> walkThrouhHallway() const;
                
                // findPathToAndOutOfRoom function that returns a vector of pairs
                // of integers. Each pair represents a cell in the grid map
                // that is part of the path into and out of the room in the maze.
                std::vector<std::pair<int, int>> findPathToAndOutOfRoom() const;

                // findWindingPath function that returns a vector of pairs
                // of integers. Each pair represents a cell in the grid map
                // that is part of the winding path in the maze.
                std::vector<std::pair<int, int>> findWindingPath() const;

                // solveMaze function that returns a vector of pairs
                // of integers. Each pair represents a cell in the grid map
                // that is part of the path from the start to the end of the maze.
                std::vector<std::pair<int, int>> solveMaze() const;

            private:
                std::vector<std::vector<int>> grid_map;
                bool is_initialized;

                // performColumnWalk function that performs a column walk
                // in a hallway, starting from the given row and column index
                void performColumnWalk(std::vector<std::pair<int, int>>& hallway_cells, const int& row_index, const int& col_index) const;
                
                // performRowWalk function that performs a row walk
                // in a hallway, starting from the given row and column index
                void performRowWalk(std::vector<std::pair<int, int>>& hallway_cells, const int& row_index, const int& col_index) const;

                // searchAColumnForEmptySpace function that searches
                // a column of the grid map for empty space
                int searchAColumnForEmptySpace(const int col_index) const;
        };
    }

    namespace graph
    {
        // performSimpleDFS function that performs a simple DFS
        // on the given grid map and returns a vector of pairs
        // of integers. Each pair represents a cell in the grid map
        // that is part of the path. DFS is rejected if there are forks.
        // See assumption in the README.md file.
        void performSimpleDFS(std::vector<std::vector<int>> const& grid_map, const int& row_index, const int& col_index, std::vector<std::pair<int, int>>& path);

        // Node class that represents a node in the A* algorithm
        class Node
        {
            public:
                Node(const int& row_index, const int& col_index);
                ~Node();

                // getters and setters
                const int& getFScore() const;
                const int& getGScore() const;
                const int& getParentRowIndex() const;
                const int& getParentColIndex() const;
                const int& getRowIndex() const;
                const int& getColIndex() const;

                void setGScore(const int& g_score);
                void setFScore(const int& f_score);
                void setHScore(const int& h_score);
                void setParentRowIndex(const int& parent_row_index);
                void setParentColIndex(const int& parent_col_index);

                // operator overloading for the < operator
                // used for sorting the nodes in the priority queue
                bool operator<(const Node& node) const;

            private:
                int row_index;
                int col_index;
                int g_score;
                int f_score;
                int h_score;
                int parent_row_index;
                int parent_col_index;
        };
        
        // performAStar function that performs the A* algorithm
        void performAStar(std::vector<std::vector<int>> const& grid_map, const int& start_row_index, const int& start_col_index, const int& end_row_index, const int& end_col_index, std::vector<std::pair<int, int>>& path);
    }
}

#endif /* MAZE_H */