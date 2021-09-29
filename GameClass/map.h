#include <ncurses.h>

class Map{
    
public:
    Map(int v, int h, char node);
    void Set_Index(int x, int y, char obj);
    void Set_Index(vector<int> coor, char obj);
    char Get_Index(vector<int> coor);
    void Print_Arena();
    void Refresh();
    bool OutOfBounds(vector<int> pos);
    
private: 
    int horizontal;
    int vertical;
    char empty_node;
    vector<vector<char>> arena;
    vector<vector<char>> emptyMap; 

};


Map::Map(int v, int h, char node = ' '){
    empty_node = node;
    vertical = v;
    horizontal = h;
    arena = vector<vector<char>>(vertical, vector<char>(horizontal, empty_node));
    emptyMap = arena; 
}
void Map::Set_Index(int x, int y, char obj){                        // Set a character at specified Index.
    if(x < 0 || x > horizontal || y < 0 || y > vertical) return;
    arena[x][y] = obj;
}
void Map::Set_Index(vector<int> coor, char obj){
    if(coor[0] < 0 || coor[0] > horizontal || coor[1] < 0 || coor[1] > vertical) return;
    arena[coor[0]][coor[1]] = obj;
}
char Map::Get_Index(vector<int> coor){                  // Get Character in specified index.
    return arena[coor[0]][coor[1]];
} 
void Map::Print_Arena(){                                // Draw the map, with borders and all.
    
    printw("  SNAKE GAME BY SANDEEP\n");
    for(int k = 0; k < horizontal+3; k++){
        printw("_ ");
    }
    printw("\n");
    for(int i = 0; i < vertical; i++){
        printw(" | ");
        for(int j = 0; j < horizontal; j++){
            addch(arena[i][j]); addch(' ');
        }
        printw("|\n");
        
    }
    for(int k = 0; k < horizontal+3; k++){
        printw("_ ");
    }
    printw("\n");
}
void Map::Refresh(){
    arena = emptyMap;                               // Reset Map to Initial. 
}
bool Map::OutOfBounds(vector<int> pos){             // Check if Given coordinates is within the map.
    if(pos[0] < 0 || pos [0] >= horizontal || pos[1] >= vertical || pos[1] < 0 ){printw("\nOuch! You Hit the Wall");return true;}
    return false;               
}