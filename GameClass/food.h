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
    timer = rand() % random_additional_time + min_timer;
    pos = { rand() % (maxLength -1), rand() % (maxWidth -1)} ;
}
        
vector<int> Food::getPos(){
    return pos;
}
int Food::getTimer(){
    return timer;
}
bool Food::Food::timerDown(){
    timer--;
    if(timer) return false;
    return true;
}