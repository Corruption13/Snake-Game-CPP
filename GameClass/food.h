class Food{
public:
    Food(int length, int width);
    void spawn_food(int min_timer, int random_additional_time);
    vector<int> getPos();
    int getTimer();
    bool timerDown();

private:
    int maxLength;
    int maxWidth;
    vector<int> pos;
    int timer; 
} ;



Food::Food(int length, int width){
    maxLength = length;
    maxWidth = width;
    timer = 100;
    pos = { rand() % (maxLength -1), rand() % (maxWidth -1)} ;
}
void Food::spawn_food(int min_timer, int random_additional_time){
    timer = rand() % random_additional_time + min_timer;                // Timer before food is respawned. Haven't Implemented.
    pos = { rand() % (maxLength -1), rand() % (maxWidth -1)} ;          // Spawn Food Randomly.
}
        
vector<int> Food::getPos(){
    return pos;
}
int Food::getTimer(){
    return timer;
}
bool Food::Food::timerDown(){                   // Reduce Food Life Duration. Return True if expired food.
    timer--;
    if(timer) 
        return false;
    //or just spawn_food(10, 10);
    return true;
}