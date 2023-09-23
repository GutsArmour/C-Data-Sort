#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

std::vector<std::pair<std::string, std::string>> sort(std::vector<std::pair<std::string, std::string>> & wall) {
    std::vector<std::pair<std::string, std::string>> sorted;
    auto first = * (wall.begin());
    sorted.push_back(first);

    //Forward loop
    bool found = true;
    do {
        auto item = find_if(wall.begin(), wall.end(), [&](auto item){return item.first == sorted.back().second;});
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
        auto item = find_if(wall.begin(), wall.end(), [&](auto item){return item.second == sorted.front().first;});
        if (item != wall.end()){
            sorted.insert(sorted.begin(), *item);
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

    std::vector<std::pair<std::string, std::string>> wall {};

    auto start = std::chrono::high_resolution_clock::now();
    //Load data
    while (std::getline(filehandle,line)) {
        noOfPairs++;
        std::istringstream ss (line);
        std::string symbol1, symbol2;
        std::getline(ss, symbol1, ',');
        std::getline(ss, symbol2);
        ss >> symbol1 >> symbol2;
        wall.push_back({symbol1, symbol2});
    }

    //Sort and output timing data
    auto sorted = sort(wall);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);

    std::cout << "Number of input pairs: " << noOfPairs << std::endl;
    std::cout << "Nanoseconds taken to load and sort in memory: " << duration.count() << std::endl;
}
