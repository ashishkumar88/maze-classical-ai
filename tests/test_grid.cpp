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

// Test search on map file with multiple rows and invalid hallway maze
TEST(GridTest, HallwayWalk1)
{
    string map_file_path = "maps/invalid_hallway_maze.txt";
    maze::grid::Grid grid(map_file_path);
    auto hallway = grid.walkThrouhHallway();
    ASSERT_EQ(hallway.size(), 0);
}

// Test search on map file with multiple rows and valid hallway maze with column hallway
TEST(GridTest, HallwayWalk2)
{
    string map_file_path = "maps/hallway_maze_1.txt";
    maze::grid::Grid grid(map_file_path);
    auto hallway = grid.walkThrouhHallway();
    ASSERT_EQ(hallway.size(), 6);
    ASSERT_EQ(hallway[0].first, 0);
    ASSERT_EQ(hallway[0].second, 3);
    ASSERT_EQ(hallway[hallway.size() - 1].first, 5);
    ASSERT_EQ(hallway[hallway.size() - 1].second, 3);
}


// Test search on map file with multiple rows and valid hallway maze with column hallway
TEST(GridTest, HallwayWalk3)
{
    string map_file_path = "maps/hallway_maze_2.txt";
    maze::grid::Grid grid(map_file_path);
    auto hallway = grid.walkThrouhHallway();
    ASSERT_EQ(hallway.size(), 5);
    ASSERT_EQ(hallway[0].first, 1);
    ASSERT_EQ(hallway[0].second, 3);
    ASSERT_EQ(hallway[4].first, 5);
    ASSERT_EQ(hallway[4].second, 3);
}

// Test search on map file with multiple rows and valid hallway maze with column hallway
TEST(GridTest, HallwayWalk4)
{
    string map_file_path = "maps/hallway_maze_3.txt";
    maze::grid::Grid grid(map_file_path);
    auto hallway = grid.walkThrouhHallway();
    ASSERT_EQ(hallway.size(), 5);
    ASSERT_EQ(hallway[0].first, 0);
    ASSERT_EQ(hallway[0].second, 3);
    ASSERT_EQ(hallway[4].first, 4);
    ASSERT_EQ(hallway[4].second, 3);
}

// Test search on map file with multiple rows and valid hallway maze with row hallway
TEST(GridTest, HallwayWalk5)
{
    string map_file_path = "maps/hallway_maze_4.txt";
    maze::grid::Grid grid(map_file_path);
    auto hallway = grid.walkThrouhHallway();
    ASSERT_EQ(hallway.size(), 9);
    ASSERT_EQ(hallway[0].first, 4);
    ASSERT_EQ(hallway[0].second, 0);
    ASSERT_EQ(hallway[hallway.size() - 1].first, 4);
    ASSERT_EQ(hallway[hallway.size() - 1].second, 8);
}

// Test search on map file with multiple rows and valid hallway maze with row hallway
TEST(GridTest, HallwayWalk6)
{
    string map_file_path = "maps/hallway_maze_5.txt";
    maze::grid::Grid grid(map_file_path);
    auto hallway = grid.walkThrouhHallway();
    ASSERT_EQ(hallway.size(), 8);
    ASSERT_EQ(hallway[0].first, 4);
    ASSERT_EQ(hallway[0].second, 0);
    ASSERT_EQ(hallway[7].first, 4);
    ASSERT_EQ(hallway[7].second, 7);
}

// Test search on map file with multiple rows and invalid room in a maze
TEST(GridTest, RoomPath1)
{
    string map_file_path = "maps/invalid_room_1.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 0);
}

// Test search on map file with multiple rows and invalid room in a maze
TEST(GridTest, RoomPath2)
{
    string map_file_path = "maps/invalid_room_2.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 0);
}

// Test search on map file with multiple rows and valid room in a maze
TEST(GridTest, RoomPath3)
{
    string map_file_path = "maps/room_maze_1.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 7);
    ASSERT_EQ(path[0].first, 0);
    ASSERT_EQ(path[0].second, 1);
    ASSERT_EQ(path[6].first, 3);
    ASSERT_EQ(path[6].second, 4);
}

// Test search on map file with multiple rows and valid room in a maze
TEST(GridTest, RoomPath4)
{
    string map_file_path = "maps/room_maze_2.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 7);
    ASSERT_EQ(path[0].first, 0);
    ASSERT_EQ(path[0].second, 1);
    ASSERT_EQ(path[6].first, 2);
    ASSERT_EQ(path[6].second, 5);
}

// Test search on map file with multiple rows and valid room in a maze
TEST(GridTest, RoomPath5)
{
    string map_file_path = "maps/room_maze_3.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 7);
    ASSERT_EQ(path[0].first, 1);
    ASSERT_EQ(path[0].second, 0);
    ASSERT_EQ(path[6].first, 3);
    ASSERT_EQ(path[6].second, 4);
}

// Test search on map file with multiple rows and valid room in a maze
TEST(GridTest, RoomPath6)
{
    string map_file_path = "maps/room_maze_4.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 9);
    ASSERT_EQ(path[0].first, 1);
    ASSERT_EQ(path[0].second, 0);
    ASSERT_EQ(path[8].first, 5);
    ASSERT_EQ(path[8].second, 4);
}

// Test search on map file with multiple rows and room without exit
TEST(GridTest, RoomPath7)
{
    string map_file_path = "maps/room_maze_5.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 0);
}

// Test search on map file with multiple rows and room with invalid exits
TEST(GridTest, RoomPath8)
{
    string map_file_path = "maps/room_maze_6.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 0);
}

// Test search on map file with multiple rows and room with invalid exits
TEST(GridTest, RoomPath9)
{
    string map_file_path = "maps/room_maze_7.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findPathToAndOutOfRoom();
    ASSERT_EQ(path.size(), 0);
}

// Test winding path following on map file with multiple rows and invalid winding path
TEST(GridTest, WindingPath1)
{
    string map_file_path = "maps/invalid_winding_path_maze_1.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findWindingPath();
    ASSERT_EQ(path.size(), 0);
}

// Test winding path following on map file with multiple rows and valid winding path
TEST(GridTest, WindingPath2)
{
    string map_file_path = "maps/winding_path_maze_1.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findWindingPath();
    ASSERT_EQ(path.size(), 13);
    ASSERT_EQ(path[0].first, 0);
    ASSERT_EQ(path[0].second, 1);
    ASSERT_EQ(path[12].first, 6);
    ASSERT_EQ(path[12].second, 3);
}

// Test winding path following on map file with multiple rows and valid winding path
TEST(GridTest, WindingPath3)
{
    string map_file_path = "maps/winding_path_maze_2.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.findWindingPath();
    ASSERT_EQ(path.size(), 42);
    ASSERT_EQ(path[0].first, 5);
    ASSERT_EQ(path[0].second, 0);
    ASSERT_EQ(path[41].first, 2);
    ASSERT_EQ(path[41].second, 22);
}

// Test solving maze on map file with multiple rows and invalid maze
TEST(GridTest, SolveMaze1)
{
    string map_file_path = "maps/invalid_start_end_maze_1.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.solveMaze();
    ASSERT_EQ(path.size(), 0);
}

// Test solving maze on map file with multiple rows and invalid maze
TEST(GridTest, SolveMaze2)
{
    string map_file_path = "maps/invalid_start_end_maze_2.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.solveMaze();
    ASSERT_EQ(path.size(), 0);
}

// Test solving maze on map file with multiple rows and invalid maze
TEST(GridTest, SolveMaze3)
{
    string map_file_path = "maps/invalid_start_end_maze_3.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.solveMaze();
    ASSERT_EQ(path.size(), 0);
}

// Test solving maze on map file with multiple rows and valid maze
TEST(GridTest, SolveMaze4)
{
    string map_file_path = "maps/start_end_maze_1.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.solveMaze();
    ASSERT_EQ(path.size(), 8);
    ASSERT_EQ(path[0].first, 0);
    ASSERT_EQ(path[0].second, 1);
    ASSERT_EQ(path[7].first, 5);
    ASSERT_EQ(path[7].second, 3);
}

// Test solving maze on map file with multiple rows and valid maze
TEST(GridTest, SolveMaze5)
{
    string map_file_path = "maps/start_end_maze_2.txt";
    maze::grid::Grid grid(map_file_path);
    auto path = grid.solveMaze();
    ASSERT_EQ(path.size(), 17);
    ASSERT_EQ(path[0].first, 0);
    ASSERT_EQ(path[0].second, 1);
    ASSERT_EQ(path[16].first, 8);
    ASSERT_EQ(path[16].second, 9);
}

int main(int ac, char* av[]) {
    testing::InitGoogleTest(&ac, av);    
    return RUN_ALL_TESTS();
}