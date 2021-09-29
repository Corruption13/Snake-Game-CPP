#include <ncurses.h>

class Player{

public:
    Player(int x_init, int y_init, char skin1 );
    void eat();
    int getLength();
    vector<vector<int>> getBodyPosition();
    char getDirection();
    vector<int> getNextHeadPos();
    void setDirection(char dir);
    char getSkin();
    void Move();
    void Cascade_Snake(int y, int x);
    bool isPartOfSnake(vector<int> pos);


private:
    vector<int> headPos;
    vector<vector<int>> body;
    char skin;
    bool isAlive;
    int length;
    char direction; // W, A, S, D
};


Player::Player(int x_init, int y_init, char skin1 = '0'){
    isAlive = true; 
    skin = skin1;
    length = 1;
    direction = 'd';
    headPos = {x_init, y_init};
    body.push_back(headPos);
}



void Player::eat(){
    length++;
    body.push_back(body.back());
}
int Player::getLength(){
    return length;
}
vector<vector<int>> Player::getBodyPosition(){
    return body;
}
char Player::getDirection(){
    return direction;
}
vector<int> Player::getNextHeadPos(){
    if(direction == 'd'){
        headPos[1]++;
    }
    if(direction == 'w'){
        headPos[0]--;
    }
    if(direction == 'a'){
        headPos[1]--;
    }
    if(direction == 's'){
        headPos[0]++;
    }
    return headPos;
}
void Player::setDirection(char dir){
    if(dir == 'a' && direction == 'd')return;
    if(dir == 'w' && direction == 's')return;
    if(dir == 's' && direction == 'w')return;
    if(dir == 'd' && direction == 'a')return;
    direction = dir ;
}
char Player::getSkin(){
    return skin;
}
void Player::Move(){

    if(direction == 'd'){
        Cascade_Snake(body[0][0], body[0][1] + 1); 
    }
    if(direction == 'w'){
        Cascade_Snake(body[0][0] - 1, body[0][1]); 
    }
    if(direction == 'a'){
        Cascade_Snake(body[0][0], body[0][1] - 1); 
    }
    if(direction == 's'){
        Cascade_Snake(body[0][0] + 1, body[0][1]); 
    }
}

void Player::Cascade_Snake(int y, int x){
    for(int i = length-1; i > 0; i--){
        body[i] = body[i-1];
    }
    body[0] = {y, x};
    headPos = {y, x};
};

bool Player::isPartOfSnake(vector<int> pos){
    if(count(body.begin(), body.end(), pos)){printw("\nYou Ate Yourself!"); return true;}
    return false;
}

