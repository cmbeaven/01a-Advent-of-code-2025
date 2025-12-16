/**
 * 08.cpp
 * 
 * Find the circuits for 3 dimensional puzzle boxes
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <algorithm>

struct pos{
    int x;
    int y;
    int z;
    const bool operator==(const pos& p2){return (this->x == p2.x && this->y == p2.y && this->z == p2.z);}
    const bool operator!=(const pos& p2){return !(this->x == p2.x && this->y == p2.y && this->z == p2.z);}
};

double findDistance(pos& p1,pos& p2){
    return std::hypot(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z);
}

struct circuit{
    std::vector<pos> boxes;
};

void printCircuit(circuit& c){
    for(auto b : c.boxes){
        printf("(%i,%i,%i),",b.x,b.y,b.z);
    }
}

void printCircuits(std::vector<circuit>& v){
    for(auto c : v){
        printCircuit(c);
        printf("\n");
    }
}

int findBox(std::vector<circuit>& v, pos& p){
    for(int i = 0; i < v.size(); ++i){
        for(auto b : v[i].boxes){
            if(b == p)
                return i;
        }
    }
    return -1;
}

class distanceGraph{
    public:
        distanceGraph(std::vector<pos>& boxes);
        int combineNearestCircuit();
        std::vector<circuit>& getCircuits(){
            return circuits;
        }
        void printGraph();
    private:
        void makeDistances();
        std::vector<circuit> circuits;
        std::vector<std::vector<double>> distances;
};

int main(){
    std::vector<pos> boxes;
    while(!std::cin.eof()){
        std::string inputLine;
        getline(std::cin,inputLine);
        int prevCursor = 0;
        int cursor = 0;
        cursor = inputLine.find(',');
        pos box;
        box.x = std::stoi(inputLine.substr(prevCursor,cursor));
        prevCursor = ++cursor;
        cursor = inputLine.find(',',cursor);
        box.y = std::stoi(inputLine.substr(prevCursor,cursor-prevCursor));
        box.z = std::stoi(inputLine.substr(cursor + 1, inputLine.length()-cursor));
        boxes.push_back(box);
    }

    // for(auto box : boxes){
    //     printf("%i,%i,%i\n",box.x,box.y,box.z);
    // }

    std::vector<std::vector<double>> distances;
    distances.resize(boxes.size());
    for(int i = 0; i < boxes.size(); i++){
        distances[i].resize(boxes.size());
    }
    // distance from i -> j
    for(int i = 0; i < distances.size(); i++){
        for(int j = 0; j < distances.size(); j++){
            distances[i][j] = findDistance(boxes[i],boxes[j]);
        }
    }

    std::vector<std::pair<int,int>> connections;
    for(int n = 0; n < (boxes.size() == 20 ? 10 : 1000); n++){
        int b1 = 0;
        int b2 = 1;
        double dLowest = distances[0][1];
        for (int i = 0; i < distances.size(); i++){
            for(int j = 0; j < i; j++){
                if(distances[i][j] != 0 && distances[i][j] < dLowest){
                    b1 = i;
                    b2 = j;
                    dLowest = distances[i][j];
                }
            }
        }
        connections.push_back(std::pair<int,int>(b1,b2));
        distances[b1][b2] = 0;
        distances[b2][b1] = 0;
    }

    // for(auto c : connections){
    //     printf("(%i,%i,%i)-(%i,%i,%i)\n",boxes[c.first].x,boxes[c.first].y,boxes[c.first].z,boxes[c.second].x,boxes[c.second].y,boxes[c.second].z);
    // }

    std::vector<circuit> circuits;
    for(auto box : boxes){
        circuit newCircuit;
        newCircuit.boxes.push_back(box);
        circuits.push_back(newCircuit);
    }
    printf("%zu\n", circuits.size());
    printCircuits(circuits);
    printf("///////////////////////////////////////////\n");
    for(auto c : connections){
        int c1 = findBox(circuits, boxes[c.first]);
        int c2 = findBox(circuits, boxes[c.second]);
        printf("(%i,%i,%i)-(%i,%i,%i)|",boxes[c.first].x,boxes[c.first].y,boxes[c.first].z,boxes[c.second].x,boxes[c.second].y,boxes[c.second].z);
        printf("%i,%i\n",c1,c2);
        if(c1 == -1 && c2 == -1){
            circuit temp;
            temp.boxes.push_back(boxes[c.first]);
            temp.boxes.push_back(boxes[c.second]);
            circuits.push_back(temp);
        }
        else if(c1 == -1){
            circuits[c2].boxes.push_back(boxes[c.first]);
        }
        else if(c2 == -1){
            circuits[c1].boxes.push_back(boxes[c.second]);
        }
        else if(c1 != c2){
            // need to combine both circuits
            for(auto box : circuits[c2].boxes){
                circuits[c1].boxes.push_back(box);
            }
            circuits[c2].boxes.clear();
            circuits.erase(circuits.begin() + c2);
        printCircuits(circuits);
        printf("///////////////////////////////////////////\n");
         }
    }
    std::sort(circuits.begin(), circuits.end(),[](circuit a,circuit b){return a.boxes.size() > b.boxes.size();});
    printCircuits(circuits);

    long sum = circuits[0].boxes.size() * circuits[1].boxes.size() * circuits[2].boxes.size();
    printf("Multiplicand: %li\n",sum);




    // distanceGraph dGraph(boxes);
    // printCircuits(dGraph.getCircuits());
    // printf("///////////////////////////////////////////\n");
    // for(int i = 0; i < 10; i++){
    //     dGraph.combineNearestCircuit();
    //     printCircuits(dGraph.getCircuits());
    //     printf("///////////////////////////////////////////\n");
    // }

    return 0;
}

distanceGraph::distanceGraph(std::vector<pos>& boxes){
    for(auto box : boxes){
        circuit newCircuit;
        newCircuit.boxes.push_back(box);
        circuits.push_back(newCircuit);
    }
    makeDistances();
}

int distanceGraph::combineNearestCircuit(){
    int c1 = 0;
    int c2 = 1;
    double dLowest = distances[0][1];
    for (int i = 0; i < distances.size(); i++){
        for(int j = 0; j < i; j++){
            if(distances[i][j] != 0 && distances[i][j] < dLowest){
                c1 = i;
                c2 = j;
                dLowest = distances[i][j];
            }
        }
    }
    // need to combine circuits together
    // add boxes in c2 to c1
    for(auto box : circuits[c2].boxes){
        circuits[c1].boxes.push_back(box);
    }
// circuits[c2].boxes.clear();
    // null all distances between c1 and other boxes to min(c1->c? and c2->c?)
    for(int i = 0; i < distances.size(); i++){
        double minDist = std::min(distances[c1][i],distances[c2][i]);
        distances[c1][i] = minDist;
        distances[i][c1] = minDist;
    }
    // null distances of c2->c? and c?->c2
    for(int i = 0; i < distances.size(); i++){
        distances[i][c2] = 0;
    }
    for(auto d : distances[c2]){
        d = 0;
    }

    // printf("%i,%i,%i - %i,%i,%i\n",circuits[c1].boxes[0].x,circuits[c1].boxes[0].y,circuits[c1].boxes[0].z,\
    // circuits[c2].boxes[0].x,circuits[c2].boxes[0].y,circuits[c2].boxes[0].z);
    return dLowest;
}

void distanceGraph::makeDistances(){
    distances.clear();
    distances.resize(circuits.size());
    for(int i = 0; i < circuits.size(); i++){
        distances[i].resize(circuits.size());
    }
    // distance from i -> j
    for(int i = 0; i < distances.size(); i++){
        for(int j = 0; j < distances.size(); j++){
            distances[i][j] = findDistance(circuits[i].boxes[0],circuits[j].boxes[0]);
        }
    }
    printGraph();
}

void distanceGraph::printGraph(){
   for(auto v : distances){
        for(auto d : v){
            printf("%4.0f| ",d);
        }
        printf("\n");
    }
}