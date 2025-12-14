/**
 * 04.cpp
 * 
 * Helps the elves maximize their efficiency in the printing dept.
 */

#include <iostream>
#include <vector>
#include <string>
#include <string_view>

class charMatrix{
    public:
        struct matrixSize_t{
            int height;
            int width;
        };
        void addRow(std::string_view row);
        char getLocation(int x, int y);
        matrixSize_t getSize();
    private:
        int rowLength = 0;
        std::vector<std::string> matrix;
};

bool accessible(charMatrix& matrix, int x, int y);

int main(int argv, char** argc){
    charMatrix printFloor;
    while(!std::cin.eof()){
        std::string inputLine;
        getline(std::cin,inputLine);
        printFloor.addRow(inputLine);
    }
    charMatrix::matrixSize_t size = printFloor.getSize();

    int sum = 0;
    for(int i = 0; i < size.height; ++i){
        for(int j = 0; j < size.width; ++j){
            if(accessible(printFloor,i,j)){
                sum++;
            }
            std::cout << printFloor.getLocation(i,j);
        }
        std::cout << '\n' << std::flush;
    }
    printf("Accessible: %i\n",sum);
    return 0;
}

void charMatrix::addRow(std::string_view row){
    if(rowLength == 0)
        rowLength = row.length();
    else if(rowLength != row.length())
        return;
    matrix.push_back(row.data());
}
char charMatrix::getLocation(int x, int y){
    // check bounds
    if(x < 0)
        return 0;
    if(y < 0)
        return 0;
    if(y > rowLength)
        return 0;
    if(x > matrix.size())
        return 0;
    
    return matrix[x][y];
}

charMatrix::matrixSize_t charMatrix::getSize(){
    matrixSize_t size;
    size.height = matrix.size();
    size.width = rowLength;
    return size;
}
// accessbile if less than 4 @ around it
bool accessible(charMatrix& matrix, int x, int y){
    int count = 0;
    for(int i = -1; i < 2; ++i){
        for(int j = -1; j < 2; ++j){
            if(i == 0 && j == 0)
                continue;
            if(matrix.getLocation(x+i, y+j) == '@'){
                count++;
                if(count == 4)
                    return false;
            }
        }
    }
    return true;
}
