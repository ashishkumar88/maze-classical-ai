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
    }
}