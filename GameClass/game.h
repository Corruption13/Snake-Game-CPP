#include "food.h"
#include "map.h"
#include "player.h"
#include "utility.h"
class Game{

public:

    Game(int height, int width, int sleep1, char player_skin, char map_background);
    void GameLoop();
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
    activeGame = true;
    empty_node = '.' ;
    points = 0;
    sleep = sleep1;
    m = new Map(height, width, empty_node);
    p = new Player(height/2, width/4, '0');
    f = new Food(height, width);
    m->Set_Index(height/2, width/4, p->getSkin());

    UpdateGame();
    DrawGame();
}

void Game::GameLoop(){
        while(activeGame){
            input = readEnteredKey();
            p->setDirection(input);
            while(!PressKey()){
                UpdateGame();
                DrawGame();  
                sleepms(sleep);
                if(!activeGame) break;
            }

        }
        printw("\nGAME OVER!");
        sleepms(5000);
        getch();
}



void Game::GenerateNewFood(){
    while(true){
        f->spawn_food(10, 10);
        if(m->Get_Index(f->getPos()) == empty_node) break;
    }
}



void Game::UpdateGame(){
    
    p->Move();
    m->Refresh();

    vector<int> nextPos = p->getNextHeadPos();
    vector<vector<int>> pos = p->getBodyPosition();
    if(m->OutOfBounds(pos[0]) || p->isPartOfSnake(nextPos)){
        activeGame = false;
        return;
    }
    if(f->getPos() == pos[0]){
        p->eat(); 
        points++; 
        f->spawn_food(10, 10);
    }
    
    //Update Map
    for(int i = 0; i < pos.size(); i++){
        m->Set_Index(pos[i], p->getSkin());
    }
    m->Set_Index(f->getPos(), 'X');
}

void Game::DrawGame(){
    move(0, 0);
    refresh();

    // /* Debug Stats
    vector<int> foodPos = f->getPos();
    vector<int> playerPos = p->getNextHeadPos();
    printw("\n(Food = %d:%d | ", foodPos[0], foodPos[1]) ;
    printw("Player = %d:%d)\n", playerPos[0], playerPos[1]) ;
    printw("[Difficulty: %d]\n", (1000 - sleep)/50);
    // */
    m->Print_Arena();
    printw("\n\nSCORE: [%d]\n", points);


    
}