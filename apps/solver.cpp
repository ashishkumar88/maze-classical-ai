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
#include <filesystem>

// project includes
#include "maze.hpp"

using namespace std;

void printPath(vector<pair<int, int>> const& path)
{
    cout << "Path Start -> ";
    for(auto const& p : path)
    {
        cout << "(" << p.first << ", " << p.second << ")" << " -> ";
    }
    cout << "End" << endl;
}

int main(int argc, char** argv) 
{
    if(argc < 2)
    {
        cerr << "Usage: " << argv[0] << " -m <map_file_path> <optional: -u> <optional: user story number>" << endl;
        return 1;
    }
    else
    {
        int user_story_id = 5;
        int col_index = -1;
        string map_file = "";

        for (int i = 1; i < argc; i++) {
            string flag = argv[i];
            if (flag.compare(string("-m")) == 0 && i + 1 < argc) {
                map_file = argv[i+1];
            } else if (flag.compare(string("-u")) == 0 && i + 1 < argc) {
                int value_provided = stoi(argv[i + 1]);
                if(value_provided >= 1 && value_provided <= 5)
                {
                    user_story_id = value_provided;
                }
            } 
        }

        filesystem::path map_file_path(map_file);
        maze::grid::Grid grid(map_file_path);

        switch (user_story_id)
        {
            case 1:
                {
                    if(int col_index = grid.searchARowForEmptySpace(0); col_index != maze::grid::Constants::INDEX_NOT_FOUND)
                    {
                        cout << "First empty space in row " << 1 << " is at column " << col_index + 1 << endl;
                    }
                    else
                    {
                        cout << "No empty space in row #"<< 1 <<" or an error occured." << endl;
                    }
                    break;
                }
            case 2:
                {
                    auto path = grid.walkThrouhHallway();
                    if(path.size() > 0)
                    {
                        printPath(path);
                    }
                    else
                    {
                        cout << "No path found or an error occured." << endl;
                    }
                    break;
                }
            case 3:
                {
                    auto path = grid.findPathToAndOutOfRoom();
                    if(path.size() > 0)
                    {
                        printPath(path);
                    }
                    else
                    {
                        cout << "No path found or an error occured." << endl;
                    }
                    break;
                }
            case 4:
                {
                    auto path = grid.findWindingPath();
                    if(path.size() > 0)
                    {
                        printPath(path);
                    }
                    else
                    {
                        cout << "No path found or an error occured." << endl;
                    }
                    break;
                }
            case 5:
                {
                    auto path = grid.solveMaze();
                    if(path.size() > 0)
                    {
                        printPath(path);
                    }
                    else
                    {
                        cout << "No path found or an error occured." << endl;
                    }
                    break;
                }
            default:
                break;
        }
    }
    return 0;
}