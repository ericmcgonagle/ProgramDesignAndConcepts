#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

/**
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
char **loadLevel(const string &fileName, int &maxRow, int &maxCol, Player &player)
{
    ifstream inputFile(fileName);
    int playerRowStart;
    int playerColStart;
    char tile;
    bool hasDoor;
    if (!(inputFile.is_open()))
    {
        return nullptr;
    }
    inputFile >> maxRow;
    if (inputFile.fail())
    {
        inputFile.close();
        return nullptr;
    }
    if (maxRow <= 0)
    {
        inputFile.close();
        return nullptr;
    }
    inputFile >> maxCol;
    if (inputFile.fail())
    {
        inputFile.close();
        return nullptr;
    }
    if (maxCol <= 0)
    {
        inputFile.close();
        return nullptr;
    }
    if ((INT32_MAX / (double)maxRow < maxCol))
    {
        inputFile.close();
        return nullptr;
    }
    inputFile >> playerRowStart;
    if (inputFile.fail())
    {
        inputFile.close();
        return nullptr;
    }
    else if ((playerRowStart >= maxRow) || (playerRowStart < 0))
    {
        inputFile.close();
        return nullptr;
    }
    else
    {
        player.row = playerRowStart;
    }
    inputFile >> playerColStart;
    if (inputFile.fail())
    {
        inputFile.close();
        return nullptr;
    }
    else if ((playerColStart >= maxCol) || (playerColStart < 0))
    {
        inputFile.close();
        return nullptr;
    }
    else
    {
        player.col = playerColStart;
    }

    // load the map
    char **map = createMap(maxRow, maxCol);
    for (int i = 0; i < maxRow; i++)
    {
        for (int k = 0; k < maxCol; k++)
        {
            inputFile >> tile;
            if (inputFile.fail())
            {
                deleteMap(map, maxRow);
                inputFile.close();
                return nullptr;
            }
            if ((i != maxRow) && (k != maxCol))
            {
                if (inputFile.eof())
                {
                    deleteMap(map, maxRow);
                    inputFile.close();
                    return nullptr;
                }
            }
            if (tile == TILE_TREASURE)
            {
                map[i][k] = TILE_TREASURE;
            }
            else if (tile == TILE_AMULET)
            {
                map[i][k] = TILE_AMULET;
            }
            else if (tile == TILE_MONSTER)
            {
                map[i][k] = TILE_MONSTER;
            }
            else if (tile == TILE_PILLAR)
            {
                map[i][k] = TILE_PILLAR;
            }
            else if (tile == TILE_DOOR)
            {
                map[i][k] = TILE_DOOR;
                hasDoor = true;
            }
            else if (tile == TILE_EXIT)
            {
                map[i][k] = TILE_EXIT;
                hasDoor = true;
            }
            else if (tile == TILE_OPEN)
            {
                map[i][k] = TILE_OPEN;
            }
            else if (tile == TILE_PLAYER)
            {
                deleteMap(map, maxRow);
                inputFile.close();
                return nullptr;
            }
            else
            {
                deleteMap(map, maxRow);
                inputFile.close();
                return nullptr;
            }
        }
    }

    inputFile >> tile;
    if (!inputFile.eof())
    {
        deleteMap(map, maxRow);
        inputFile.close();
        return nullptr;
    }

    if (!hasDoor)
    {
        deleteMap(map, maxRow);
        inputFile.close();
        return nullptr;
    }

    // TODO: spawn player on map given player can spawn there
    map[player.row][player.col] = TILE_PLAYER;
    /*
    if (map[player.row][player.col] == TILE_OPEN)
    {
        map[player.row][player.col] = TILE_PLAYER;
    }
    else
    {
        deleteMap(map, maxRow);
        cout << "Invalid spawn point for player" << endl;
        return nullptr;
    }
    */
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int &nextRow, int &nextCol)
{
    if (input == MOVE_UP)
    {
        nextRow -= 1;
    }
    else if (input == MOVE_DOWN)
    {
        nextRow += 1;
    }
    else if (input == MOVE_LEFT)
    {
        nextCol -= 1;
    }
    else if (input == MOVE_RIGHT)
    {
        nextCol += 1;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char **createMap(int maxRow, int maxCol)
{
    if ((maxRow <= 0) || (maxCol <= 0))
    {
        return nullptr;
    }
    else if ((INT32_MAX / maxRow < maxCol))
    {
        return nullptr;
    }
    else
    {
        char **mapArray = new char *[maxRow];
        for (int i = 0; i < maxRow; i++)
        {
            mapArray[i] = new char[maxCol];
        }
        return mapArray;
    }
    return nullptr;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char **&map, int &maxRow)
{

    for (int j = 0; j < maxRow; j++)
    {
        delete[] map[j];
        map[j] = nullptr;
    }
    delete[] map;
    map = nullptr;
    maxRow = 0;
}

/**
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
char **resizeMap(char **map, int &maxRow, int &maxCol)
{
    if (map == nullptr)
    {
        return nullptr;
    }
    else if ((maxRow < 1) || (maxCol < 1))
    {
        return nullptr;
    }
    else
    {
        maxRow *= 2;
        maxCol *= 2;
        char **newMap = new char *[maxRow];
        for (int i = 0; i < maxRow; i++)
        {
            newMap[i] = new char[maxCol];
        }
        // form top right of new map
        for (int j = 0; j < maxRow / 2; j++)
        {
            for (int k = 0; k < maxCol / 2; k++)
            {
                if (map[j][k] == TILE_PLAYER)
                {
                    newMap[j][k + (maxCol / 2)] = TILE_OPEN;
                }
                else
                {
                    newMap[j][k + (maxCol / 2)] = map[j][k];
                }
            }
        }

        // form bottom left of new map
        for (int j = 0; j < maxRow / 2; j++)
        {
            for (int k = 0; k < maxCol / 2; k++)
            {
                if (map[j][k] == TILE_PLAYER)
                {
                    newMap[j + (maxRow / 2)][k] = TILE_OPEN;
                }
                else
                {
                    newMap[j + (maxRow / 2)][k] = map[j][k];
                }
            }
        }

        // form bottom right of new map
        for (int j = 0; j < maxRow / 2; j++)
        {
            for (int k = 0; k < maxCol / 2; k++)
            {
                if (map[j][k] == TILE_PLAYER)
                {
                    newMap[j + (maxRow / 2)][k + (maxCol / 2)] = TILE_OPEN;
                }
                else
                {
                    newMap[j + (maxRow / 2)][k + (maxCol / 2)] = map[j][k];
                }
            }
        }

        // copy the top left of the map to the newMap
        for (int j = 0; j < maxRow / 2; j++)
        {
            for (int k = 0; k < maxCol / 2; k++)
            {
                newMap[j][k] = map[j][k];
            }
            delete[] map[j];
        }
        delete[] map;
        return newMap;
    }
}

/**
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
int doPlayerMove(char **map, int maxRow, int maxCol, Player &player, int nextRow, int nextCol)
{
    // int status;
    // check if the next row or col is out of bounds
    if ((nextRow == maxRow) || (nextRow < 0) || (map[nextRow][player.col] == TILE_PILLAR) || (map[nextRow][player.col] == TILE_MONSTER))
    {
        nextRow = player.row;
        return STATUS_STAY;
    }
    else if ((nextCol == maxCol) || (nextCol < 0) || (map[player.row][nextCol] == TILE_PILLAR) || (map[player.row][nextCol] == TILE_MONSTER))
    {
        nextCol = player.col;
        return STATUS_STAY;
    }

    // check if next row or col is treasure
    if (map[nextRow][nextCol] == TILE_TREASURE)
    {
        player.treasure += 1;
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_TREASURE;
    }
    // check if next position is amulet tile
    else if (map[nextRow][nextCol] == TILE_AMULET)
    {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_AMULET;
    }

    // check if next position is on a door
    else if (map[nextRow][nextCol] == TILE_DOOR)
    {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_LEAVE;
    }

    // check if next position is on an exit
    else if (map[nextRow][nextCol] == TILE_EXIT)
    {
        if (player.treasure == 0)
        {
            return STATUS_STAY;
        }
        else
        {
            map[player.row][player.col] = TILE_OPEN;
            map[nextRow][nextCol] = TILE_PLAYER;
            player.row = nextRow;
            player.col = nextCol;
            return STATUS_ESCAPE;
        }
    }
    else if (map[nextRow][nextCol] == TILE_OPEN)
    {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_MOVE;
    }

    return 0;
}

/**
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
bool doMonsterAttack(char **map, int maxRow, int maxCol, const Player &player)
{
    // start checking above the player
    for (int i = player.row - 1; i >= 0; i--)
    {
        if (map[i][player.col] == TILE_PILLAR)
        {
            break;
        }
        if (map[i][player.col] == 'M')
        {
            map[i + 1][player.col] = 'M';
            map[i][player.col] = TILE_OPEN;
        }
    }

    // start checking below the player
    for (int i = player.row + 1; i < maxRow; i++)
    {
        if (map[i][player.col] == TILE_PILLAR)
        {
            break;
        }
        if (map[i][player.col] == 'M')
        {
            map[i - 1][player.col] = 'M';
            map[i][player.col] = TILE_OPEN;
        }
    }

    // checking to the right of the player
    for (int i = player.col + 1; i < maxCol; i++)
    {
        if (map[player.row][i] == TILE_PILLAR)
        {
            break;
        }
        if (map[player.row][i] == 'M')
        {
            map[player.row][i - 1] = 'M';
            map[player.row][i] = TILE_OPEN;
        }
    }

    // check to the left of the player
    for (int i = player.col - 1; i >= 0; i--)
    {
        if (map[player.row][i] == TILE_PILLAR)
        {
            break;
        }
        if (map[player.row][i] == 'M')
        {
            map[player.row][i + 1] = 'M';
            map[player.row][i] = TILE_OPEN;
        }
    }

    if (TILE_MONSTER == map[player.row][player.col])
    {
        return true;
    }

    return false;
}
