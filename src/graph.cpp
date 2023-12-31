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
#include <stack>
#include <set>
#include <stdexcept>
#include <iostream>

// project includes
#include "maze.hpp"

namespace maze
{
    namespace graph
    {
        using namespace std;

        // getAllNeighbors function that returns the valid neighbors of a node
        // Use this if full DFS is required
        vector<pair<int, int>> getAllNeighbors(vector<vector<int>> const& grid_map, const int& row_index, const int& col_index, const int& number_rows, const int& number_cols)
        {
            vector<pair<int, int>> neighbors;

            // check for left neighbor
            if (col_index - 1 >= 0 && grid_map[row_index][col_index - 1] == 0)
            {
                neighbors.push_back(make_pair(row_index, col_index - 1));
            }

            // check for right neighbor
            if (col_index + 1 < number_cols && grid_map[row_index][col_index + 1] == 0)
            {
                neighbors.push_back(make_pair(row_index, col_index + 1));
            }

            // check for top neighbor
            if (row_index - 1 >= 0 && grid_map[row_index - 1][col_index] == 0)
            {
                neighbors.push_back(make_pair(row_index - 1, col_index));
            }

            // check for bottom neighbor
            if (row_index + 1 < number_rows && grid_map[row_index + 1][col_index] == 0)
            {
                neighbors.push_back(make_pair(row_index + 1, col_index));
            }

            return neighbors;
        }

        // getWindingPathNeighbors function that returns the valid neighbors of a node
        vector<pair<int, int>> getWindingPathNeighbors(vector<vector<int>> const& grid_map, const int& row_index, const int& col_index, const int& number_rows, const int& number_cols)
        {
            vector<pair<int, int>> neighbors = getAllNeighbors(grid_map, row_index, col_index, number_rows, number_cols);

            if(neighbors.size() <= 2)
            {
                return neighbors;
            }
            else
            {   
                cout << neighbors.size() << endl;   
                throw invalid_argument("Invalid map.");
            }
        }

        void performSimpleDFS(vector<vector<int>> const& grid_map, const int& row_index, const int& col_index, vector<pair<int, int>>& path)
        {
            stack<pair<int, int>> stack_for_dfs; // although not required because of assumptions, but using stack for dfs
            set<pair<int, int>> visited_nodes;
            
            // push the starting node to the stack
            // and mark it as visited
            stack_for_dfs.push(make_pair(row_index, col_index));
            visited_nodes.insert(make_pair(row_index, col_index));

            int number_rows = grid_map.size();
            int number_cols = grid_map[0].size();

            // iterate until the stack is empty
            while (!stack_for_dfs.empty())
            {
                auto current_node = stack_for_dfs.top();
                path.push_back(current_node);
                stack_for_dfs.pop();

                try
                {
                    // get the neighbors of the current node
                    // and push them to the stack if they are not visited
                    for(auto neighbor : getWindingPathNeighbors(grid_map, current_node.first, current_node.second, number_rows, number_cols))
                    {
                        if (visited_nodes.find(neighbor) == visited_nodes.end())
                        {
                            stack_for_dfs.push(neighbor);
                            visited_nodes.insert(neighbor);
                        }
                    }
                }
                catch(const invalid_argument& e)
                {
                    throw invalid_argument("Invalid map.");
                }

            }
            
        }
    }
}