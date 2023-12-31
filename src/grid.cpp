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

// stl includes
#include <iostream>
#include <algorithm> 

// project includes
#include "maze.hpp"

namespace maze
{
    namespace grid
    {
        using namespace std;

        Grid::Grid(string const& map_file_path)
        {
            try
            {
                grid_map = readMap(map_file_path);
                is_initialized = true;
            }
            catch(const exception& e)
            {
                cerr << e.what() << '\n';
                is_initialized = false;
            }           
        }

        Grid::~Grid()
        {
            grid_map.clear();
        }

        const vector<vector<int>>& Grid::getGridMap() const
        {
            return grid_map;
        }

        void Grid::initializeGridMap(string const& map_file_path)
        {
            try
            {
                grid_map = readMap(map_file_path);
                is_initialized = true;
            }
            catch(const exception& e)
            {
                cerr << e.what() << '\n';
                is_initialized = false;
            }           
        }

        const bool& Grid::isInitialized() const
        {
            return is_initialized;
        }

        int Grid::searchARowForEmptySpace(const int row_index) const
        {
            if(!is_initialized)
            {
                cerr << "Grid map is not initialized." << endl;
                return Constants::INDEX_NOT_FOUND;
            }
            else if(grid_map.empty())
            {
                cerr << "Grid map is empty." << endl;
                return Constants::INDEX_NOT_FOUND;
            }
            else if(row_index < 0 || row_index >= grid_map.size())
            {
                cerr << "Row index is out of bounds." << endl;
                return Constants::INDEX_NOT_FOUND;
            }
            else if(grid_map[row_index].empty())
            {
                cerr << "Given row of the map is empty." << endl;
                return Constants::INDEX_NOT_FOUND;
            }
            else
            {
                if(auto row_itr = find(grid_map[row_index].begin(), grid_map[row_index].end(), 0); row_itr != grid_map[row_index].end())
                {
                    return row_itr - grid_map[row_index].begin();
                }
                else
                {
                    return Constants::INDEX_NOT_FOUND;
                }
            }

            return Constants::INDEX_NOT_FOUND;
        }

        vector<pair<int, int>> Grid::walkThrouhHallway() const
        {
            vector<pair<int, int>> hallway_cells;

            if(!is_initialized)
            {
                cerr << "Grid map is not initialized." << endl;
                return hallway_cells;
            }
            else if(grid_map.empty())
            {
                cerr << "Grid map is empty." << endl;
                return hallway_cells;
            }
            else
            {
                int number_rows = grid_map.size();
                int number_cols = grid_map[0].size();

                for(int row_index = 0; row_index < number_rows; row_index++)
                {
                    int col_index = searchARowForEmptySpace(row_index);
                    if(col_index != Constants::INDEX_NOT_FOUND)
                    {
                        if(row_index + 1 < number_rows && grid_map[row_index + 1][col_index] == 0)
                        {
                            // column hallway found
                            performColumnWalk(hallway_cells, row_index, col_index);

                            return hallway_cells;
                        }
                        else if(col_index + 1 < number_cols && grid_map[row_index][col_index + 1] == 0)
                        {
                            // row hallway found
                            performRowWalk(hallway_cells, row_index, col_index);
                            
                            return hallway_cells;
                        }
                        else
                        {
                            // just one cell
                            hallway_cells.push_back(make_pair(row_index, col_index));
                            return hallway_cells;
                        }
                    }
                }
            }

            return hallway_cells;
        }

        void Grid::performColumnWalk(vector<pair<int, int>>& hallway_cells, const int& row_index, const int& col_index) const
        {
            int number_rows = grid_map.size();
            int number_cols = grid_map[0].size();

            hallway_cells.push_back(make_pair(row_index, col_index));
            int row_ctr = row_index + 1;
            while(row_ctr < number_rows && grid_map[row_ctr][col_index] == 0)
            {
                hallway_cells.push_back(make_pair(row_ctr, col_index));
                row_ctr++;
            }
        }

        void Grid::performRowWalk(vector<pair<int, int>>& hallway_cells, const int& row_index, const int& col_index) const
        {
            int number_rows = grid_map.size();
            int number_cols = grid_map[0].size();

            hallway_cells.push_back(make_pair(row_index, col_index));
            int col_ctr = col_index + 1;
            while(col_ctr < number_cols && grid_map[row_index][col_ctr] == 0)
            {
                hallway_cells.push_back(make_pair(row_index, col_ctr));
                col_ctr++;
            }
        }

        vector<pair<int, int>> Grid::findPathToAndOutOfRoom() const
        {
            vector<pair<int, int>> path;

            if(!is_initialized)
            {
                cerr << "Grid map is not initialized." << endl;
                return path;
            }
            else if(grid_map.empty())
            {
                cerr << "Grid map is empty." << endl;
                return path;
            }
            else
            {
                int number_rows = grid_map.size();
                int number_cols = grid_map[0].size();

                for(int row_index = 0; row_index < number_rows; row_index++)
                {
                    int col_index = searchARowForEmptySpace(row_index); // entrance cell may have been found
                    
                    if(col_index != Constants::INDEX_NOT_FOUND)
                    {   
                        // make sure that the room is valid, see assumptions in the README.md file
                        if(row_index + 1 < number_rows && grid_map[row_index + 1][col_index] == 0 && col_index + 1 < number_cols && grid_map[row_index][col_index + 1] == 0)
                        {
                            cerr << "Invalid room." << endl;
                            return {};
                        }

                        cout << "Found empty space at row " << row_index + 1 << " and column " << col_index + 1 << endl;

                        if(row_index + 1 < number_rows && grid_map[row_index + 1][col_index] == 0)
                        {
                            // room found below
                            path.clear();
                            path.push_back(make_pair(row_index, col_index));
                            performColumnWalk(path, row_index + 1, col_index);

                            if(path.size() > 2)
                            {
                                auto last_element = path.back();
                                performRowWalk(path, last_element.first, last_element.second + 1);

                                // check if the last is outside the room
                                last_element = path.back();
                                if((last_element.first + 1 < number_rows && grid_map[last_element.first + 1][last_element.second] == 1 && grid_map[last_element.first - 1][last_element.second] == 1)
                                    || (last_element.first + 1 == number_rows && grid_map[last_element.first - 1][last_element.second] == 1)
                                )
                                {
                                    // this is exit
                                    return path;
                                }
                                else if((grid_map[last_element.first - 1][last_element.second] == 0)
                                    && (last_element.first + 1 < number_rows && grid_map[last_element.first + 1][last_element.second] == 0))
                                {
                                    // add the exit
                                    path.push_back(make_pair(last_element.first + 1, last_element.second));
                                    return path;
                                }
                                else
                                {                                
                                    cerr << "Invalid room." << endl;
                                    return {};
                                }
                            }
                            else
                            {                                
                                cerr << "Invalid room. Must be atleast 2 cells wide." << endl; // See assumption in the README.md file  
                                return {};
                            }
                        }
                        else if(col_index + 1 < number_cols && grid_map[row_index][col_index + 1] == 0)
                        {
                            // room found to the right
                            path.clear();
                            path.push_back(make_pair(row_index, col_index));
                            performRowWalk(path, row_index, col_index + 1);

                            if(path.size() > 2)
                            {
                                auto last_element = path.back();
                                performColumnWalk(path, last_element.first + 1, last_element.second);

                                // check if the last is outside the room
                                last_element = path.back();
                                if((last_element.second + 1 < number_cols && grid_map[last_element.first][last_element.second + 1] == 1 && grid_map[last_element.first][last_element.second - 1] == 1)
                                    || (last_element.second + 1 == number_cols && grid_map[last_element.first][last_element.second - 1] == 1)
                                )
                                {
                                    // this is exit
                                    return path;
                                }
                                else if((grid_map[last_element.first][last_element.second - 1] == 0)
                                    && (last_element.second + 1 < number_cols && grid_map[last_element.first][last_element.second + 1] == 0))
                                {
                                    // add the exit
                                    path.push_back(make_pair(last_element.first, last_element.second + 1));
                                    return path;
                                }
                                else
                                {                                
                                    cerr << "Invalid room." << endl;
                                    return {};
                                }
                            }
                            else
                            {
                                cerr << "Invalid room. Must be atleast 2 cells wide." << endl; // See assumption in the README.md file  
                                return {};
                            }
                        }
                        else
                        {
                            cerr << "No room found." << endl;
                            return {};
                        }
                    }
                }
            }

            return path; // TODO: Explore using graph search algorithms 
        }
    }
}