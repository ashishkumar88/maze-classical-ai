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
#include <algorithm>
#include <unordered_map>

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
                throw invalid_argument("Invalid map.");
            }
        }

        Node::Node(const int& row_index, const int& col_index)
        {
            this->row_index = row_index;
            this->col_index = col_index;
            this->g_score = 0;
            this->h_score = 0;
            this->f_score = 0;
            this->parent_col_index = -1;
            this->parent_row_index = -1;
        }

        Node::~Node()
        {
        }

        const int& Node::getFScore() const
        {
            return this->f_score;
        }

        const int& Node::getGScore() const
        {
            return this->g_score;
        }

        const int& Node::getParentRowIndex() const
        {
            return this->parent_row_index;
        }

        const int& Node::getParentColIndex() const
        {
            return this->parent_col_index;
        }

        const int& Node::getRowIndex() const
        {
            return this->row_index;
        }

        const int& Node::getColIndex() const
        {
            return this->col_index;
        }

        void Node::setGScore(const int& g_score)
        {
            this->g_score = g_score;
        }

        void Node::setFScore(const int& f_score)
        {
            this->f_score = f_score;
        }

        void Node::setHScore(const int& h_score)
        {
            this->h_score = h_score;
        }

        void Node::setParentRowIndex(const int& parent_row_index)
        {
            this->parent_row_index = parent_row_index;
        }

        void Node::setParentColIndex(const int& parent_col_index)
        {
            this->parent_col_index = parent_col_index;
        }

        bool Node::operator<(const Node& node) const
        {
            if(this->f_score == node.f_score)
            {
                return this->h_score + 10 * this->row_index < node.h_score + 10 * node.row_index;
            }
            else
            {
                return this->h_score < node.h_score;
            }
        }

        void performSimpleDFS(vector<vector<int>> const& grid_map, const int& row_index, const int& col_index, vector<pair<int, int>>& path)
        {
            int number_rows = grid_map.size();
            int number_cols = grid_map[0].size();

            if(row_index < 0 || row_index >= number_rows || col_index < 0 || col_index >= number_cols)
            {
                throw invalid_argument("Invalid start cell.");
            }
            
            stack<pair<int, int>> stack_for_dfs; // although not required because of assumptions, but using stack for dfs
            set<pair<int, int>> visited_nodes;
            
            // push the starting node to the stack
            // and mark it as visited
            stack_for_dfs.push(make_pair(row_index, col_index));
            visited_nodes.insert(make_pair(row_index, col_index));

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

        struct hash_pair_ints {
            template <class T1, class T2>
            size_t operator()(const pair<T1, T2>& p) const
            {
                auto hash_of_first = hash<T1>{}(p.first);
                auto hash_of_second = hash<T2>{}(p.second);
        
                if (hash_of_first != hash_of_second) {
                    return hash_of_first ^ hash_of_second;              
                }
                return hash_of_first;
            }
        };

        void performAStar(vector<vector<int>> const& grid_map, const int& start_row_index, const int& start_col_index, const int& end_row_index, const int& end_col_index, vector<pair<int, int>>& path)
        {
            int number_rows = grid_map.size();
            int number_cols = grid_map[0].size();

            if(start_row_index < 0 || start_row_index >= number_rows || start_col_index < 0 || start_col_index >= number_cols)
            {
                throw invalid_argument("Invalid start cell.");
            }       

            if(end_row_index < 0 || end_row_index >= number_rows || end_col_index < 0 || end_col_index >= number_cols)
            {
                throw invalid_argument("Invalid end cell.");
            }

            // create a priority queue of nodes
            // and push the starting node to it
            set<Node> open_list;
            open_list.insert(Node(start_row_index, start_col_index));
            set<pair<int, int>> visited_nodes;
            unordered_map<pair<int, int>, pair<int, int>, hash_pair_ints> child_parent_map  ;

            // iterate until the open list is empty
            while(!open_list.empty())
            {
                Node current_node = *open_list.begin();

                open_list.erase(open_list.begin());

                // check if the current node is the goal node
                if(current_node.getRowIndex() == end_row_index && current_node.getColIndex() == end_col_index)
                {
                    // backtrack the path
                    
                    pair<int, int> current_node = make_pair(end_row_index, end_col_index);

                    while(current_node.first != start_row_index || current_node.second != start_col_index)
                    {
                        path.push_back(current_node);
                        current_node = child_parent_map[current_node];
                    }

                    path.push_back(current_node);
                    reverse(path.begin(), path.end());
                    return;                    
                }

                // add the current node to the closed list
                visited_nodes.insert(make_pair(current_node.getRowIndex(), current_node.getColIndex()));

                // get the neighbors of the current node
                for(auto neighbor : getAllNeighbors(grid_map, current_node.getRowIndex(), current_node.getColIndex(), number_rows, number_cols))
                {
                    if(visited_nodes.find(neighbor) == visited_nodes.end())
                    {
                        int g_score = current_node.getGScore() + 1;
                        int h_score = abs(neighbor.first - end_row_index) + abs(neighbor.second - end_col_index);
                        int f_score = g_score + h_score;

                        // check if the neighbor is already in the open list
                        // sadly, an O(n) operation. Priority queues do not support search
                        bool found = false;
                        for(auto node : open_list)
                        {
                            if(node.getRowIndex() == neighbor.first && node.getColIndex() == neighbor.second)
                            {
                                if(node.getFScore() > f_score)
                                {
                                    node.setGScore(g_score);
                                    node.setFScore(f_score);
                                    node.setHScore(h_score);
                                    node.setParentColIndex(current_node.getColIndex());
                                    node.setParentRowIndex(current_node.getRowIndex());
                                    child_parent_map[neighbor] = make_pair(current_node.getRowIndex(), current_node.getColIndex());
                                }

                                found = true;   
                                break;
                            }
                        }

                        // if the neighbor is not in the open list
                        // add it to the open list
                        if(!found)
                        {
                            Node node(neighbor.first, neighbor.second);
                            node.setGScore(g_score);
                            node.setFScore(f_score);
                            node.setHScore(h_score);
                            node.setParentColIndex(current_node.getColIndex());
                            node.setParentRowIndex(current_node.getRowIndex());
                            child_parent_map[neighbor] = make_pair(current_node.getRowIndex(), current_node.getColIndex());
                            open_list.insert(node);
                        }
                    }

                }
            }
        }
    }
}