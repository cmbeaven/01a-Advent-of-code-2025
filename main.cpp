/*
    main.cpp

    Find the passcode to the North Pole based on rotations
*/

#include <iostream>
#include <sstream>
#include <vector>

enum dir{
    none,
    left,
    right
};

struct rotation{
    dir direction;
    int distance;
};

class dial{
    public:
    int turn(rotation turnBy);
    int getLoc();
    dial(int start);
    private:
    int location;
};

int main(int argv, char** argc){

    std::vector<rotation> rotations;

    while(!std::cin.eof()){
        std::string inputLine;
        getline(std::cin,inputLine);
        rotation turn;
        if(inputLine[0] == 'R')
            turn.direction = right;
        if(inputLine[0] == 'L')
            turn.direction = left;
        turn.distance = std::stoi(inputLine.substr(1,inputLine.length()));
        rotations.push_back(turn);
    }
    dial knob(50);
    int timesAtZero = 0;
    for(auto turn : rotations){
        timesAtZero += knob.turn(turn);
        //if(knob.getLoc() == 0){
        //    ++timesAtZero;
        //}
        printf("Direction: %s Distance: %i\n\
Loc: %i Zeros: %i\n",turn.direction == left ? "LEFT" : "RIGHT",turn.distance,knob.getLoc(),timesAtZero);
    }
    printf("times at zero: %i\n",timesAtZero);
    return 0;
}


dial::dial(int start){
    location = start;
}

int dial::turn(rotation turnBy){
    int pointsAtZero = 0;
    switch(turnBy.direction){
        case left:
            if(location == 0){
                location += 100;
            }            
            location -= turnBy.distance;
            while(location < 0){
                location += 100;
                ++pointsAtZero;
            }
            if(location == 0)
                ++pointsAtZero;
            break;
        case right:
            location += turnBy.distance;
            while(location >= 100){
                location -= 100;
                ++pointsAtZero;
            }
            break;
        default:
            break;
    }
    return pointsAtZero;
}

int dial::getLoc(){
    return location;
}