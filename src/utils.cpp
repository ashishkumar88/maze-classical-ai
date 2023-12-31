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
#include <filesystem>
#include <iostream>
#include <fstream>

// project includes
#include "maze.hpp"

namespace maze
{
    namespace grid
    {
        using namespace std;

        vector<vector<int>> readMap(filesystem::path const& map_file_path)
        {
            vector<vector<int>> grid_map;

            // check if the file exists
            if (!filesystem::is_regular_file(map_file_path))    
            {
                cerr << "File does not exist : " << map_file_path << endl;
                throw filesystem::filesystem_error("File does not exist.", error_code());
            }
            else 
            {
                ifstream map_file_handler;
                string map_row;
                int first_row_size = -1;
                int row_counter = -1;

                map_file_handler.open(map_file_path);

                // check if the file is open
                if(!map_file_handler.is_open())
                {
                    cerr << "Could not open file : " << map_file_path << endl;
                    throw filesystem::filesystem_error("Could not open file..", error_code());
                }
            
                // read lines from the file and add them to the grid map
                while(getline(map_file_handler, map_row))
                {
                    int map_row_size = map_row.size();

                    // check if the map is valid
                    // map is invalid if the size of the rows are not equal
                    // size of the first row is considered as the size of the rows
                    if(first_row_size == -1)
                    {
                        first_row_size = map_row_size;
                    }
                    else if(first_row_size != map_row_size)
                    {
                        cerr << "Invalid map file : " << map_file_path << endl;
                        throw invalid_argument("Invalid map file.");
                    }

                    grid_map.push_back(vector<int>(first_row_size));
                    ++row_counter;

                    for(int i = 0; i < first_row_size; i++)
                    {
                        if(map_row[i] != '0' && map_row[i] != '1')
                        {
                            cerr << "Invalid map file : " << map_file_path << endl;
                            throw invalid_argument("Invalid map file.");
                        }
                        grid_map[row_counter][i] = map_row[i] - '0';
                    }
                }

                map_file_handler.close();
            }

            return grid_map;
        }
    }
}