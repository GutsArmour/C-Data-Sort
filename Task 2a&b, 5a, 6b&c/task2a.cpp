#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>

std::list<std::pair<std::string, std::string>> sort(std::map<std::string, std::string> & wall, std::map<std::string, std::string> & wallReverse) {
    std::list<std::pair<std::string, std::string>> sorted;
    auto firstBrick = * (wall.begin());
    sorted.push_back(firstBrick);

    //Forward loop
    bool found = true;
    do {
        auto brick = wall.find(sorted.back().second);
        if (brick != wall.end()){
            sorted.push_back(*brick);
        }
        else {
            found = false;
        }
    } while (found);

    //Reverse loop
    found = true;
    do {
        auto brick = wallReverse.find(sorted.front().first);
        if (brick != wallReverse.end()){
            sorted.push_front({brick->second, brick->first});
        }
        else {
            found = false;
        }
    } while (found);

    return sorted;
}

int main(int argc, char* argv[]){
    std::string filepath = argv[1];
    std::ifstream filehandle {filepath};
    std::string line;

    std::map<std::string, std::string> wall {};
    std::map<std::string, std::string> wallReverse {};

    //Load data
    while (getline(filehandle,line)) {
        std::istringstream ss (line);
        std::string symbol1, symbol2;
        getline(ss, symbol1, ',');
        getline(ss, symbol2);
        ss >> symbol1 >> symbol2;
        wall.insert({symbol1, symbol2});
        wallReverse.insert({symbol2, symbol1});
    }

    //Sort and output data
    auto sorted = sort(wall, wallReverse);
    for (auto item: sorted) {
        std::cout << item.first << std::endl;
    }
    std::cout << sorted.back().second << std::endl;
}
