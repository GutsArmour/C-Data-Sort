#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

std::vector<std::pair<std::string, std::string>> sort(std::vector<std::pair<std::string, std::string>> & wall) {
    std::vector<std::pair<std::string, std::string>> sorted;
    auto firstBrick = * (wall.begin());
    sorted.push_back(firstBrick);

    //Forward loop
    bool found = true;
    do {
        auto brick = find_if(wall.begin(), wall.end(), [&](auto item){return item.first == sorted.back().second;});
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
        auto brick = find_if(wall.begin(), wall.end(), [&](auto item){return item.second == sorted.front().first;});
        if (brick != wall.end()){
            sorted.insert(sorted.begin(), *brick);
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

    std::vector<std::pair<std::string, std::string>> wall {};

    //Load data
    while (getline(filehandle,line)) {
        std::istringstream ss (line);
        std::string symbol1, symbol2;
        getline(ss, symbol1, ',');
        getline(ss, symbol2);
        ss >> symbol1 >> symbol2;
        wall.push_back({symbol1, symbol2});
    }

    //Sort and output data
    auto sorted = sort(wall);
    for (auto item: sorted) {
        std::cout << item.first << std::endl;
    }
    std::cout << sorted.back().second << std::endl;
}
