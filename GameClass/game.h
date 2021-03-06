#include "food.h"
#include "map.h"
#include "player.h"
#include "utility.h"
class Game{

public:

    Game(int height, int width, int sleep1, char player_skin, char map_background);
    void GameLoop();
    void ResponsiveGameLoopExperimental();
    void GenerateNewFood();
    void UpdateGame();
    void DrawGame();

private:

    Player *p;
    Map *m;
    Food *f;

    unsigned long int points;
    char empty_node;
    bool activeGame;
    char input;
    int sleep;

};


Game::Game(int height, int width, int sleep1, char player_skin, char map_background){

    activeGame = true;                                  // When Over, set to False.
    empty_node = '.' ;                                  
    points = 0;
    sleep = sleep1; 
    m = new Map(height, width, empty_node);
    p = new Player(height/2, width/4, '0');
    f = new Food(height, width);
    m->Set_Index(height/2, width/4, p->getSkin());      // Set Starting position of player in map middle.

    UpdateGame();
    DrawGame();
}

void Game::GameLoop(){                                  // Main Game Loop.
        
        while(activeGame){
            input = readEnteredKey();                   // User Input
            //p->setDirection(input);                   //// Dev Note: Putting setDirection here makes input more responsive, but you can eat yourself by trying to 180 real quick.
            while(!PressKey()){                         
                p->setDirection(input);                 //// But Putting it here makes it less responsive but more correct. Sigh What do.
                UpdateGame();
                DrawGame();         
                sleepms(sleep);                 
                if(!activeGame) break;                  // To Prevent case where game continues till key is pressed.
            }
        }

        printw("\n\nGAME OVER!\n");                     // End Game.
        getch();
}

void Game::ResponsiveGameLoopExperimental(){         // More Responsive Structure. But quick 180 kills your snake.
        
        while(activeGame){
            input = readEnteredKey();                   
            p->setDirection(input);                   
            while(!PressKey()){                         
                //p->setDirection(input);                
                UpdateGame();
                DrawGame();         
                sleepms(sleep);                 
                if(!activeGame) break;                  
            }
        }

        printw("\n\nGAME OVER!\n");                     
        getch();
}



void Game::GenerateNewFood(){
    while(true){
        f->spawn_food(10, 10);
        if(m->Get_Index(f->getPos()) == empty_node) break;  // If Node is empty, valid spot for food.
    }
}



void Game::UpdateGame(){
    
    p->Move();                                                      // Move Snake as needed.
                                                      

    vector<int> nextPos = p->getNextHeadPos();
    vector<vector<int>> pos = p->getBodyPosition();
    if(m->OutOfBounds(pos[0]) || p->isPartOfSnake(pos[0])){        // If failure conditions, end game.
        activeGame = false;
        return;
    }
    if(f->getPos() == pos[0]){                                  // If Capture Food, Generate new food.
        p->eat(); 
        points+=10;   
        GenerateNewFood();
    }
    
    m->Refresh();                                               // Refresh Map and redraw objects on it.
    //Update Map
    for(int i = 0; i < pos.size(); i++){                        // Draw Objects over fresh map.
        m->Set_Index(pos[i], p->getSkin());
    }
    m->Set_Index(f->getPos(), 'X');
}

void Game::DrawGame(){                                              // MAIN UI is basically all this.
    move(0, 0);             // Move Console Cursor to Start.
    refresh();              // Clear Screen.

    // /* Debug Stats
    vector<int> foodPos = f->getPos();
    vector<int> playerPos = p->getNextHeadPos();
    printw("\nSNAKE GAME BY Sandeep Pillai");
    printw("\nStats: (Food = %d:%d | ", foodPos[0], foodPos[1]) ;
    printw("Player = %d:%d)", playerPos[0], playerPos[1]) ;
    printw("[Difficulty: %d]\n", (1000 - sleep)/50);
    // */

    m->Print_Arena();                       // Draw Map
    printw("\n\nSCORE: %d\n", points);    // Score.


    
}