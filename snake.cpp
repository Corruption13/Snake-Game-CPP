// Practice Snake Game, Designed On My Own.
// Yeah, no #ifdef directives. Oh well.
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <ncurses.h>
#include <string>
using namespace std;

#include "GameClass/game.h"

int main(){

    int height = 15;                // Map Y Dimension
    int width = 15;                 // Map X Dimension
    int sleep = 100;                // Difficulty (Lower: Harder)
    char player_skin = '0';         // Snake Skin
    char map_background = '.';      // Empty Node Character

    initscr();  
    Game *gameInstance = new Game(height, width, sleep, player_skin, map_background);
    gameInstance->GameLoop();
    endwin();                  
}