#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/** COMPLETED ////////////////////////////////////////////////////////////////
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */

char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {

    ifstream ifs(fileName);   // Opens file

    if(!ifs.is_open()) {   // Ensures file is opened successfully
        return nullptr;
    }

    if (!(ifs >> maxRow >> maxCol)) {   // Reads maxRow and maxCol values from file and if the types don't match the file is invalid
        ifs.close();
        return nullptr;
    }

    // Ensures maxRow, maxCol, and map area are within bounds
    if (maxRow <= 0 || maxCol <= 0 || maxRow >= 999999 || maxCol >= 999999 || maxRow > INT32_MAX / maxCol || maxCol > INT32_MAX / maxRow) {
        ifs.close();
        return nullptr;
    }

    if (!(ifs >> player.row >> player.col)) {   // Reads player.row and player.col values from file and if the types don't match the file is invalid
        ifs.close();
        return nullptr;
    }
    
    // Ensures player coords are within given bounds
    if (player.row < 0 || player.row >= maxRow || player.col < 0 || player.col >= maxCol) {
        ifs.close();
        return nullptr;
    }
 
    char** map = createMap(maxRow, maxCol);   // Creates map with given values from file

    if (!map) {   // Checks if the memory allocation fails
        ifs.close();
        return nullptr;
    }

    // // Varaibles used for tests
    int tileCount = 0;
    int tempDoor = 0;
    int tempExit = 0;

    for (int i = 0; i < maxRow; ++i) {
        for (int j = 0; j < maxCol; ++j) {
            if (!(ifs >> map[i][j])) {
                deleteMap(map, maxRow);
                ifs.close();
                return nullptr;
            }

            if (map[i][j] != TILE_AMULET && map[i][j] != TILE_DOOR && map[i][j] != TILE_EXIT && map[i][j] != TILE_MONSTER && map[i][j] != TILE_OPEN && map[i][j] != TILE_PILLAR && map[i][j] != TILE_PLAYER && map[i][j] != TILE_TREASURE) {
                deleteMap(map, maxRow);
                ifs.close();
                return nullptr;
            }

            if (map[i][j] == TILE_DOOR) {   // Checks for a door
                tempDoor++;
            }

            if (map[i][j] == TILE_EXIT) {   // Checks for an exit
                tempExit++;
            }

            if (ifs.fail()) {   // Checks if the stream fails
                deleteMap(map, maxRow);
                ifs.close();
                return nullptr;             
            }
            
            tileCount++;   // Updates tile count
        }
    }

    if (ifs.peek() != EOF) {   // Checks for any extra vals after the map has been read
        deleteMap(map, maxRow);
        ifs.close();
        return nullptr;
    }

    if (tempDoor + tempExit == 0) {   // Ensures there is at least one exit or door
        deleteMap(map, maxRow);
        ifs.close();
        return nullptr;
    }

    if (tileCount != maxRow * maxCol) {   // Ensures the dimensions are the same as Row * Col
        deleteMap(map, maxRow);
        ifs.close();
        return nullptr;
    }

    if (map[player.row][player.col] != TILE_OPEN) {   // Ensures player is placed on an open tile
        deleteMap(map, maxRow);
        ifs.close();
        return nullptr;
    }

    map[player.row][player.col] = TILE_PLAYER;   // Places player on map

    ifs.close(); // Closes file

    return map;
}
//////////////////////////////////////////////////////////////////////////////

/** COMPLETED ////////////////////////////////////////////////////////////////
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    // Updates correct value based on input.
    if (input == MOVE_UP) {
        nextRow--;
    } else if(input == MOVE_DOWN) {
        nextRow++;
    } else if(input == MOVE_RIGHT) {
        nextCol++;
    } else if(input == MOVE_LEFT) {
        nextCol--;
    } // If an invalid input is given, nothing will happen with the nextRow 
      // & nextCol vars meaning the player stays i.e. no movement.
}
//////////////////////////////////////////////////////////////////////////////

/** COMPLETED ////////////////////////////////////////////////////////////////
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {

    char** map = new char*[maxRow];
    
    for (int i = 0; i < maxRow; ++i) {
        map[i] = new char[maxCol];
        for (int j = 0; j < maxCol; ++j) {
            map[i][j] = TILE_OPEN;
        }
    }
    return map;
}
//////////////////////////////////////////////////////////////////////////////

/** COMPLETED ////////////////////////////////////////////////////////////////
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {

    // Checks if map is already a nullptr
    if (map == nullptr) {
        maxRow = 0;
        return;
    }

    // Deallocates all memory for each individual tile of the map.
    for (int i = 0; i < maxRow; ++i) {
        delete[] map[i];
    }

    // Deletes map and updates specified variables to default.
    delete[] map; 
    map = nullptr; 
    maxRow = 0;
}
//////////////////////////////////////////////////////////////////////////////

/** COMPLETED ////////////////////////////////////////////////////////////////
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */

char** resizeMap(char** map, int& maxRow, int& maxCol) {

    // Check if the map is initially null or dimensions are invalid
    if (map == nullptr || maxRow <= 0 || maxCol <= 0) {
        return nullptr;
    }

    // Creates a new map with doubled rows and cols
    int newMR = 2 * maxRow;
    int newMC = 2 * maxCol;
    char** newMap = createMap(newMR, newMC);

    if (map == nullptr) { // Checks if memory allocation was successful
        deleteMap(newMap, newMR);
        return nullptr;
    }
    
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            if (map[i][j] == TILE_PLAYER) {
                newMap[i][j] = TILE_PLAYER;
                newMap[i + maxRow][j + maxCol] = TILE_OPEN;
                newMap[i + maxRow][j] = TILE_OPEN;
                newMap[i][j + maxCol] = TILE_OPEN;
            } else {
                newMap[i][j] = map[i][j];
                newMap[i + maxRow][j] = map[i][j]; 
                newMap[i][j + maxCol] = map[i][j];
                newMap[i + maxRow][j + maxCol] = map[i][j];
         }
      }
   }
    // Deallocates original map
    deleteMap(map, maxRow);

    // Updates maxRow & maxCol
    maxRow = newMR;
    maxCol = newMC;

    return newMap;
}
//////////////////////////////////////////////////////////////////////////////


/** COMPLETED ////////////////////////////////////////////////////////////////
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */

int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {

    // Check if the next position is out of bounds
    if (nextRow < 0 || nextRow >= maxRow || nextCol < 0 || nextCol >= maxCol) {
        return STATUS_STAY;
    }

    // Get the tile at the next position
    char nextPos = map[nextRow][nextCol];

    // Check if the next position is a pillar or monster
    if (nextPos == TILE_PILLAR || nextPos == TILE_MONSTER) {
        return STATUS_STAY;
    }

    // If the next position is on a treasure tile, collect the LOOT
    if (nextPos == TILE_TREASURE) {
        player.treasure++;
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_TREASURE;
    }

    // If the next position is an amulet tile
    if (nextPos == TILE_AMULET) {
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_AMULET;
    }

    // If the next position is a door
    if (nextPos == TILE_DOOR) {
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_LEAVE;
    }

    // If the next position is on an exit and the player GOT loot
    if (nextPos == TILE_EXIT) {
        if (player.treasure > 0) {
            map[nextRow][nextCol] = TILE_PLAYER;
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;
            return STATUS_ESCAPE;
        } else {   // Else the next position is on an exit and the player is POVERTY
            return STATUS_STAY; 
        }
    }

    // Update map and player position
    map[nextRow][nextCol] = TILE_PLAYER;
    map[player.row][player.col] = TILE_OPEN;
    player.row = nextRow;
    player.col = nextCol;
    
    return STATUS_MOVE;
}
//////////////////////////////////////////////////////////////////////////////

/** COMPLETED ////////////////////////////////////////////////////////////////
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    // Checks above
    for (int i = player.row - 1; i >= 0; --i) {
        if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i + 1][player.col] = TILE_MONSTER;
        } else if (map[i][player.col] == TILE_PILLAR) {
            break;
        }
    }

    // Checks below
    for (int i = player.row + 1; i < maxRow; ++i) {
        if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i - 1][player.col] = TILE_MONSTER;
        } else if (map[i][player.col] == TILE_PILLAR) {
            break;
        }
    }

    // Checks left
    for (int j = player.col - 1; j >= 0; --j) {
        if (map[player.row][j] == TILE_MONSTER) {
            map[player.row][j] = TILE_OPEN;
            map[player.row][j + 1] = TILE_MONSTER;
        } else if (map[player.row][j] == TILE_PILLAR) {
            break;
        }
    }

    // Check right
    for (int j = player.col + 1; j < maxCol; ++j) {
        if (map[player.row][j] == TILE_MONSTER) {
            map[player.row][j] = TILE_OPEN;
            map[player.row][j - 1] = TILE_MONSTER;
        } else if (map[player.row][j] == TILE_PILLAR) {
            break;
        }
    }

    // Checks if monster and player are on the same tile
    if (map[player.row][player.col] == TILE_MONSTER) {
        return true; // TRUE, monsters DID kill the Adventurer
    }

    return false; // FALSE, monsters DID NOT kill the Adventurer
}
//////////////////////////////////////////////////////////////////////////////