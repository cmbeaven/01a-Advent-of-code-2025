/**
 * 05.cpp
 * 
 * Find rotten ingredients in the elves database
 */

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

typedef std::pair<long,long> range;

bool checkFresh(std::vector<range>& ranges, long ingredient);


int main(int argv, char** argc){
    
    std::string inputLine;
    std::vector<range> freshRanges;
    std::vector<long> ingredients;
    getline(std::cin,inputLine);
    do{
        int splitLocation = inputLine.find('-');
        range temp;
        temp.first = std::stol(inputLine.substr(0,splitLocation));
        temp.second = std::stol(inputLine.substr(splitLocation+1,inputLine.length()));
        std::cout << temp.first << "-" << temp.second << "\n";
        freshRanges.push_back(temp);
        getline(std::cin,inputLine);
    }while(inputLine != "");

    while(!std::cin.eof()){
        getline(std::cin,inputLine);
        ingredients.push_back(std::stol(inputLine));
        std::cout << inputLine << '\n';
    }
    int sum = 0;
    for(auto ingredient : ingredients){
        sum += checkFresh(freshRanges,ingredient);
    }
    long lsum = 0;
    // sort vector
    std::sort(freshRanges.begin(),freshRanges.end(),[](range r1, range r2) { return r1.first < r2.first;});

    for(auto r = freshRanges.begin(); r < freshRanges.end() - 1; ++r){
        if(r->second >= (r+1)->first){
            if(r->second > (r+1)->second){
                (r+1)->second = r->second;
            }
            (r+1)->first = r->first;
            r->first = 0;
            r->second = 0;
        }
    }

    for(auto range : freshRanges){
        printf("%li-%li\n",range.first,range.second);
        if(range.first != 0 && range.second != 0){
            lsum += 1 + range.second - range.first;
        }
    }

    printf("fresh: %i\n",sum);
    printf("fresh total: %li\n",lsum);


    return 0;
}


bool checkFresh(std::vector<range>& ranges, long ingredient){
    for(auto range : ranges){
        if(ingredient >= range.first && ingredient <= range.second){
            return true;
        }
    }


    return false;
}
