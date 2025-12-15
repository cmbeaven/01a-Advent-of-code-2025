/**
 * 06.cpp
 * 
 * Help a young cephalapod with his homework
 */

#include <iostream>
#include <string>
#include <vector>

 int main(int argv, char** argc){
    std::vector<std::vector<int>> lines;
    std::vector<char> operators;

    while(!std::cin.eof()){
        std::string inputLine;
        getline(std::cin, inputLine);

        int prevCursor = 0;
        int cursor = 0;
        if(inputLine[0] == '*' || inputLine[0] == '+'){
            for(auto c : inputLine){
                if(c == '*' || c == '+')
                    operators.push_back(c);
            }
            for(auto c : operators)
                printf("%c ", c);
            printf("\n");
            break;
        }

        std::vector<int> line;
        while(!isnumber(inputLine[cursor])){
            ++cursor;
        }
        prevCursor = cursor;
        while(cursor < inputLine.length()){
            while(isnumber(inputLine[cursor])){
                ++cursor;
            }
            line.push_back(std::stoi(inputLine.substr(prevCursor,cursor-prevCursor)));
            while(!isnumber(inputLine[cursor])){
                ++cursor;
            }
            prevCursor = cursor;
        }
        lines.push_back(line);

        for(auto x : line){
            printf("%i ",x);
        }
        printf("\n");
    }
    long sum = 0;
    for(int i = 0; i < lines[0].size(); i++){
        char op = operators[i];
        long temp = op == '*' ? 1 : 0;
        for(auto line : lines){
            switch(op){
                case '+':
                    temp += line[i];
                    break;
                case '*':
                    temp *= line[i];
                    break;
                default:
                    break;
            }
        }
        sum += temp;
    }
    printf("sum: %li\n",sum);

    return 0;
 }