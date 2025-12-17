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

struct line{
    long x1;
    long x2;
    long y1;
    long y2;
};

const long long findArea(tileLocation p1, tileLocation p2){
    long dx = std::abs(p1.x-p2.x) + 1;
    long dy = std::abs(p1.y-p2.y) + 1;
    return dx*dy;
}

bool checkGreen(tileLocation p, std::vector<tileLocation>& redTiles){
    // todo: find all lines from red -> red that intersect with a horizontal line across grid
    //       determine if p is on line: if yes then true
    //       determine if p is between lines 
    std::vector<line> lines;
    for(auto tile = redTiles.begin(); tile < redTiles.end()-1; tile++){
        // check if line created between two tiles crosses this x 
        if(p.x >= std::min(tile->x,(tile+1)->x) && p.x <= std::max(tile->x,(tile+1)->x) && tile->y == (tile+1)->y){
            line newLine;
            newLine.x1 = std::min(tile->x,(tile+1)->x);
            newLine.x2 = std::max(tile->x,(tile+1)->x);
            newLine.y1 = std::min(tile->y,(tile+1)->y);
            newLine.y2 = std::max(tile->y,(tile+1)->y);
            if(p.y == tile->y) return true; // if on line, return true
            lines.push_back(newLine);
        }
    }
    std::sort(lines.begin(),lines.end(),[](line l1, line l2){return l1.y1 < l2.y1;});
    for(auto line : lines){
        printf("(%li,%li,%li,%li)",line.x1,line.x2,line.y1,line.y2);
    }
    printf("\n");
    bool output = false;
    for(auto line = lines.begin(); line->y1 < p.y && line < lines.end(); line++){
        output = output ^ true;
    }
    return output;
}

bool checkAreaGreen(tileLocation p1, tileLocation p2, std::vector<tileLocation>& redTiles){
    bool green = true;
    for(int i = std::min(p1.x,p2.x); i < std::max(p1.x,p2.x); i++){
        for(int j = std::min(p1.y,p2.y);j < std::max(p1.y,p2.y); j++){
            green = green && checkGreen(tileLocation(i,j),redTiles);
        }
    }
    return green;
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

    long maxY = 0;
    long maxX = 0;
    for(auto tile : redTiles){
        if(tile.x > maxX) maxX = tile.x;
        if(tile.y > maxY) maxY = tile.y;
    }
    // create map of green and red tiles
    std::vector<std::string> tileMap;
    tileMap.reserve(maxY + 1);
    for(int i = 0; i < maxY + 1; i++){
        tileMap.push_back("");
        tileMap[i].reserve(maxX + 1);
        for(int j = 0; j < maxX + 1; j++){
            tileMap[i].append(".");
        }
    }
    for(auto tile : redTiles) tileMap[tile.y][tile.x] = '#';

    for(auto s : tileMap){
        printf("%s\n",s.c_str());
    }

    //for(auto s : tileMap) printf("%s\n",s.c_str());
    //for(auto redTiles.begin)

    // Now only red or green tiles
    //printf("%i\n",checkGreen(tileLocation(9,6),redTiles));
    // long long maxArea = 0;
    // for(int i = 0; i < redTiles.size(); i++){
    //     for(int j = 0; j < redTiles.size(); j++){
    //         if(maxArea < findArea(redTiles[i],redTiles[j]) && checkAreaGreen(redTiles[i],redTiles[j],redTiles)){
    //             maxArea = findArea(redTiles[i],redTiles[j]);
    //         }
    //     }
    // }

    printf("maxArea: %lli\n",maxArea);

    return 0;
}