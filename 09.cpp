/**
 * 09.cpp
 * 
 * Find rectangles in a grid pattern
 */

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <utility>
#include <map>

class tileLocation{
    public:
        long x;
        long y;
        tileLocation(){
            x = 0;
            y = 0;
        }
        tileLocation(long x, long y) : x(x), y(y) {}
};

class line{
public:
    long x1;
    long x2;
    long y1;
    long y2;
    line(){x1=0;x2=0;y1=0;y2=0;}
    line(long x1,long x2,long y1,long y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}
};

bool determineGreen(tileLocation p,std::vector<line>& hLine, std::vector<line>& vLine){
    // do a vertical line check first
    // vertical lines at p.y 
    std::vector<line> crossedVLine;
    for(auto l : vLine){
        if(p.y > std::min(l.y1,l.y2) && p.y < std::max(l.y1,l.y2)){
            crossedVLine.push_back(l);
        }
    }
    if(crossedVLine.size() == 0) return false;
    std::sort(crossedVLine.begin(),crossedVLine.end(),[](line l1, line l2){return l1.x1 < l2.x1;});
    for(auto l : crossedVLine){
        printf("(%li,%li,%li,%li)",l.x1,l.x2,l.y1,l.y2);
    }
    int count = 0;
    

    // then a horizontal check
    // horizontal lines at p.x
    std::vector<line> crossedHLine;
    for(auto l : hLine){
        if(p.x > std::min(l.x1,l.x2) && p.x < std::max(l.x1,l.x2)){
            crossedHLine.push_back(l);
        }
    }

    if(crossedHLine.size() == 0) return false;
    std::sort(crossedHLine.begin(),crossedHLine.end(),[](line l1, line l2){return l1.y1 < l2.y1;});

    return false;
}

const long long findArea(tileLocation p1, tileLocation p2){
    long dx = std::abs(p1.x-p2.x) + 1;
    long dy = std::abs(p1.y-p2.y) + 1;
    return dx*dy;
}

int main(int argv, char** argc){
    std::vector<tileLocation> redTiles;
    while(!std::cin.eof()){
        std::string inputLine;
        getline(std::cin,inputLine);
        int cursor = inputLine.find(',');
        tileLocation tile;
        tile.x = std::stol(inputLine.substr(0,cursor));
        tile.y = std::stol(inputLine.substr(cursor+1,inputLine.length()));
        redTiles.push_back(tile);
    }

    long long maxArea = 0;
    for(int i = 0; i < redTiles.size(); i++){
        for(int j = 0; j < redTiles.size(); j++){
            if(maxArea < findArea(redTiles[i],redTiles[j])){
                maxArea = findArea(redTiles[i],redTiles[j]);
            }
        }
    }


    //for(auto t : redTiles){printf("%li,%li\n",t.x,t.y);}

    std::set<long> xValues;
    std::set<long> yValues;
    for(auto t : redTiles){
        xValues.insert(t.x);
        yValues.insert(t.y);
    }

    std::map<long,long> condenseX;
    std::map<long,long> uncondenseX;
    long index = 0;
    for(auto x : xValues){
        condenseX.insert(std::pair<long,long>(x,index));
        uncondenseX.insert(std::pair<long,long>(index,x));
        ++index;
    }

    std::map<long,long> condenseY;
    std::map<long,long> uncondenseY;
    index = 0;
    for(auto y : yValues){
        condenseY.insert(std::pair<long,long>(y,index));
        uncondenseY.insert(std::pair<long,long>(index,y));
        ++index;
    }

    std::vector<tileLocation> condensedTiles;
    for(auto t : redTiles){
        condensedTiles.push_back(tileLocation(condenseX.find(t.x)->second,condenseY.find(t.y)->second));
    }

    for(auto t : condensedTiles){printf("%li,%li\n",t.x,t.y);}                                                    // print condensed points
    //for(auto t : condensedTiles){printf("%li,%li\n",uncondenseX.find(t.x)->second,uncondenseY.find(t.y)->second);}// print uncondensed points

    std::vector<line> hLines;
    std::vector<line> vLines;

    for(auto tile = condensedTiles.begin(); tile < condensedTiles.end()-1; ++tile){
        auto nTile = tile + 1;
        // same x, line vertical
        if(tile->x == nTile->x){
            vLines.push_back(line(tile->x,nTile->x,tile->y,nTile->y));
        }
        // same y, line horizontal
        if(tile->y == nTile->y){
            hLines.push_back(line(tile->x,nTile->x,tile->y,nTile->y));
        }
    }

    determineGreen(tileLocation(1,1),vLines,hLines);

    // for(auto l : hLines){
    //     printf("(%li,%li,%li,%li)\n",l.x1,l.x2,l.y1,l.y2);
    // }
    // for(auto l : vLines){
    //     printf("(%li,%li,%li,%li)\n",l.x1,l.x2,l.y1,l.y2);
    // }

    long long maxAreaGreen = 0;

    printf("maxArea: %lli\n",maxArea);
    printf("maxAreaGreen: %lli\n",maxAreaGreen);

    return 0;
}