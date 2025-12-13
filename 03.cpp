/**
 * 03.cpp
 * 
 * Find the maximum battery Joltage from standard input
 */

#include <iostream>
#include <vector>
#include <string>
#include <string_view>

struct battery{
    int joltage = 0;
    int position = -1;
};

int findJoltage(std::string_view batteryPack){
    battery firstMax;
    firstMax.joltage = 0;
    firstMax.position = -1;
    for(int i = 0; i < batteryPack.length()-1; i++){
        if(batteryPack[i]-'0' > firstMax.joltage){
            firstMax.joltage = batteryPack[i]-'0';
            firstMax.position = i;
        }
    }
    battery secondMax;
    secondMax.joltage = 0;
    secondMax.position = -1;
    for(int i = firstMax.position+1; i < batteryPack.length(); i++){
        if(i == firstMax.position) continue;
        if(batteryPack[i]-'0' > secondMax.joltage){
            secondMax.joltage = batteryPack[i]-'0';
            secondMax.position = i;
        }
    }
    //printf("First: %i %i Second: %i %i\n",firstMax.joltage,firstMax.position,secondMax.joltage,secondMax.position);
    if(firstMax.position > secondMax.position){
        return secondMax.joltage*10 + firstMax.joltage;
    }
    return secondMax.joltage + firstMax.joltage*10;
}

long long findLargeJoltage(std::string_view batteryPack){
    // initialize vector of 12 batteries
    std::vector<battery> batteries(12);
    int lastPos = -1;
    // finding 12 batteries
    for(int n = 0; n<12; n++){
        for(int i = lastPos+1; i < batteryPack.length()-(12-(n+1)); i++){
            if(batteryPack[i]-'0' > batteries[n].joltage){
                batteries[n].joltage = batteryPack[i]-'0';
                batteries[n].position = i;
            }
        }
        lastPos = batteries[n].position;
    }
    //for(auto batt : batteries){
    //    printf("j: %i p: %i\n",batt.joltage, batt.position);
    //}

   unsigned long long mult = 1;
    long long output = 0;
    for(int n = 11; n > -1; --n){
        output += batteries[n].joltage * mult;
        mult = mult * 10;
        printf("j: %i p: %lli\n",batteries[n].joltage, mult);
    }
    printf("%lli\n",output);
    return output;
}

int main(int argv, char** argc){

    std::vector<std::string> batteryPacks;

    while(!std::cin.eof()){
        std::string inputLine;
        getline(std::cin,inputLine);
        batteryPacks.push_back(inputLine);
    }
    long smallSum = 0;
    unsigned long long largeSum = 0;
    for(std::string_view batteryPack : batteryPacks){
        smallSum += findJoltage(batteryPack);
        //printf("%lli\n",findLargeJoltage(batteryPack));
        largeSum += findLargeJoltage(batteryPack);
    }
    printf("Small Joltage: %li\n",smallSum);
    printf("Large Joltage: %lli\n",largeSum);
    return 0;
}