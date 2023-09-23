#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <list>

std::list<std::pair<std::string, std::string>> sort(std::map<std::string, std::string> & wall, std::map<std::string, std::string> & WallReverse) {
    std::list<std::pair<std::string, std::string>> sorted;
    auto first = * (wall.begin());
    sorted.push_back(first);

    //Forward loop
    bool found = true;
    do {
        auto item = wall.find(sorted.back().second);
        if (item != wall.end()){
            sorted.push_back(*item);
        }
        else {
            found = false;
        }
    } while (found);

    //Reverse loop
    found = true;
    do {
        auto item = WallReverse.find(sorted.front().first);
        if (item != WallReverse.end()){
            sorted.push_front({item->second, item->first});
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
    int noOfPairs = 1;

    std::map<std::string, std::string> wall {};
    std::map<std::string, std::string> wallReverse {};

    auto start = std::chrono::high_resolution_clock::now();
    //Load data
    while (std::getline(filehandle,line)) {
        noOfPairs++;
        std::istringstream ss (line);
        std::string symbol1, symbol2;
        std::getline(ss, symbol1, ',');
        std::getline(ss, symbol2);
        ss >> symbol1 >> symbol2;
        wall.insert({symbol1, symbol2});
        wallReverse.insert({symbol2, symbol1});
    }

    //Sort and output timing data
    auto sorted = sort(wall, wallReverse);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);

    std::cout << "Number of input pairs: " << noOfPairs << std::endl;
    std::cout << "Nanoseconds taken to load and sort in memory: " << duration.count() << std::endl;
}
