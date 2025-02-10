#include "Labyrinth.h"
#include <string>
#include "set.h"
using namespace std;

struct Items{
    bool SPELLBOOK;
    bool POTION;
    bool WAND;
    Items(bool visited1, bool visited2, bool visited3) {
        SPELLBOOK = visited1;
        POTION = visited2;
        WAND = visited3;
    }
    bool isFull(){
        return SPELLBOOK && POTION && WAND;
    }
};
bool isPathToFreedomHelp(MazeCell* start, const string& moves, Items item);bool isPathToFreedomHelp(MazeCell* start, const string& moves, Items item){
    if(start == nullptr){
        return false;
    }
    if(start->whatsHere != Item::NOTHING){
        if(start->whatsHere == Item::POTION) item.POTION = true;
        if(start->whatsHere == Item::SPELLBOOK) item.SPELLBOOK = true;
        if(start->whatsHere == Item::WAND) item.WAND = true;
    }
    if(item.isFull()) return true;

    char elem = moves[0];
    string remainMoves = moves;
    remainMoves.erase(0, 1);

    if(elem == 'N') return isPathToFreedomHelp(start->north, remainMoves, item);
    if(elem == 'S') return isPathToFreedomHelp(start->south, remainMoves, item);
    if(elem == 'W') return isPathToFreedomHelp(start->west, remainMoves, item);
    if(elem == 'E') return isPathToFreedomHelp(start->east, remainMoves, item);
    // moves += "N";
    // if(isPathToFreedomHelp(start->north, moves, item)) return true;
    // moves.substr(moves.size() - 1);

    // moves += "W";
    // if(isPathToFreedomHelp(start->west, moves, item)) return true;
    // moves.substr(moves.size() - 1);

    // moves += "S";
    // if(isPathToFreedomHelp(start->south, moves, item)) return true;
    // moves.substr(moves.size() - 1);

    // moves += "E";
    // if(isPathToFreedomHelp(start->east, moves, item)) return true;
    // moves.substr(moves.size() - 1);

    return false;
}

bool isPathToFreedom(MazeCell* start, const string& moves) {
    /* TODO: Delete this comment and the next few lines, then implement
     * this function.
     */
    Items item(false, false, false);
    return isPathToFreedomHelp(start, moves, item);
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

