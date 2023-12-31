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
#include <stdexcept>

// external includes
#include <gtest/gtest.h>

// project includes
#include "maze.hpp"

using namespace std;

// Test constructor with valid map file path
TEST(GridTest, Constructor)
{
    string map_file_path = "maps/single_row_1.txt";
    maze::grid::Grid grid(map_file_path);
    ASSERT_TRUE(grid.isInitialized());
}

// Test constructor with invalid map file path
TEST(GridTest, Constructor2)
{
    string map_file_path = "maps/does_not_exist.txt";
    maze::grid::Grid grid(map_file_path);
    ASSERT_FALSE(grid.isInitialized());
}

// Test constructor with empty map file path
TEST(GridTest, Constructor3)
{
    string map_file_path = "";
    maze::grid::Grid grid(map_file_path);
    ASSERT_FALSE(grid.isInitialized());
}

// Test constructor with empty map file
TEST(GridTest, Constructor4)
{
    string map_file_path = "maps/empty.txt";
    maze::grid::Grid grid(map_file_path);
    auto grid_map = grid.getGridMap();
    ASSERT_TRUE(grid_map.empty());
}

// Test constructor with map file with multiple rows
TEST(GridTest, Constructor5)
{
    string map_file_path = "maps/multiple_rows.txt";
    maze::grid::Grid grid(map_file_path);
    auto grid_map = grid.getGridMap();
    ASSERT_EQ(grid_map.size(), 10);
    ASSERT_EQ(grid_map[0].size(), 10);
    ASSERT_EQ(grid_map[9].size(), 10);
}

// Test search on map file with single row
TEST(GridTest, SearchARowForEmptySpace1)
{
    string map_file_path = "maps/single_row_1.txt";
    maze::grid::Grid grid(map_file_path);
    ASSERT_EQ(grid.searchARowForEmptySpace(0), 1);
}

// Test search on map file with single row
TEST(GridTest, SearchARowForEmptySpace2)
{
    string map_file_path = "maps/single_row_2.txt";
    maze::grid::Grid grid(map_file_path);
    ASSERT_EQ(grid.searchARowForEmptySpace(0), 2);
}

// Test search on map file with single row and invalid row index
TEST(GridTest, SearchARowForEmptySpace3)
{
    string map_file_path = "maps/single_row_1.txt";
    maze::grid::Grid grid(map_file_path);
    ASSERT_EQ(grid.searchARowForEmptySpace(1), maze::grid::Constants::INDEX_NOT_FOUND);
}

// Test search on map file with multiple rows
TEST(GridTest, SearchARowForEmptySpace4)
{
    string map_file_path = "maps/multiple_rows.txt";
    maze::grid::Grid grid(map_file_path);
    ASSERT_EQ(grid.searchARowForEmptySpace(0), 0);
    ASSERT_EQ(grid.searchARowForEmptySpace(1), 0);
    ASSERT_EQ(grid.searchARowForEmptySpace(2), 0);
    ASSERT_EQ(grid.searchARowForEmptySpace(3), 3);
    ASSERT_EQ(grid.searchARowForEmptySpace(9), 1);
}

// Test search on map file with multiple rows and invalid rows
TEST(GridTest, SearchARowForEmptySpace5)
{
    string map_file_path = "maps/multiple_rows_2.txt";
    maze::grid::Grid grid(map_file_path);
    ASSERT_FALSE(grid.isInitialized());
}

int main(int ac, char* av[]) {
    testing::InitGoogleTest(&ac, av);    
    return RUN_ALL_TESTS();
}