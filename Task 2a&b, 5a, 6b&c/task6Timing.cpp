#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <chrono>

std::list<std::string> sort(std::list<std::pair<std::string, std::string>> & tapeA, std::list<std::pair<std::string, std::string>> & tapeB) {
    std::list<std::pair<std::string, std::string>> tapeC;
    std::list<std::pair<std::string, int>> tapeP;
    std::list<std::pair<std::string, int>> tapeF;

    //Part 1
    int n = tapeA.size() + 1;

    tapeB.sort([](std::pair<std::string, std::string> pair1, std::pair<std::string, std::string> pair2) {
        return pair1.first < pair2.first;
    });
    tapeA.sort([](std::pair<std::string, std::string> pair1, std::pair<std::string, std::string> pair2) {
        return pair1.second < pair2.second;
    });

    auto aIt = tapeA.begin();
    auto bIt = tapeB.begin();

    while (aIt != tapeA.end()) {
        //Step 1
        if (aIt->second == bIt->first) {
            tapeC.push_back({aIt->first, bIt->second});
            aIt++;
            bIt++;
        }
        //Step 2
        else if (aIt->second < bIt->first) {
            tapeP.push_back({aIt->first, n - 1});
            tapeP.push_back({aIt->second, n});
            aIt++;
        }
        //Step 3
        else {
            bIt++;
        }
    }

    //Part 2
    tapeP.sort([](std::pair<std::string, int> pair1, std::pair<std::string, int> pair2) {
        return pair1.first < pair2.first;
    });

    int d = 2;

    //Step 1
    while (d < n) {
        tapeA.clear();
        tapeB.clear();
        for (auto brick : tapeC) {
            tapeA.push_back(brick);
            tapeB.push_back(brick);
        }

        //Step 2
        tapeC.clear();

        //Step 3
        tapeB.sort([](std::pair<std::string, std::string> pair1, std::pair<std::string, std::string> pair2) {
            return pair1.first < pair2.first;
        });
        tapeA.sort([](std::pair<std::string, std::string> pair1, std::pair<std::string, std::string> pair2) {
            return pair1.second < pair2.second;
        });

        //Step 4
        aIt = tapeA.begin();
        bIt = tapeB.begin();
        auto pIt = tapeP.begin();
        while (aIt != tapeA.end()) {
            if (bIt != tapeB.end() && aIt->second == bIt->first) {
                tapeC.push_back({aIt->first, bIt->second});
                aIt++;
                bIt++;
            }
            else if (pIt != tapeP.end() && aIt->second == pIt->first) {
                tapeF.push_back({aIt->first, pIt->second - d});
                aIt++;
                pIt++;
            }
            else if (pIt != tapeP.end() && aIt->second > pIt->first) {
                pIt++;
            }
            else {
                bIt++;
            }
        }

        //Step 5
        tapeF.sort([](std::pair<std::string, int> pair1, std::pair<std::string, int> pair2) {
            return pair1.first < pair2.first;
        });

        //Step 6
        tapeP.merge(tapeF, [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
            return a.first < b.first;
        });

        //Step 7
        tapeF.clear();

        //Step 8
        d *= 2;
    }

    //Step 9
    tapeP.sort([](std::pair<std::string, int> pair1, std::pair<std::string, int> pair2) {
        return pair1.second < pair2.second;
    });

    std::list<std::string> result;
    for (auto item : tapeP) {
        result.push_back(item.first);
    }

    return result;
}

int main(int argc, char* argv[]){
    std::string filepath = argv[1];
    std::ifstream filehandle {filepath};
    std::string line;
    int noOfPairs = 1;

    std::list<std::pair<std::string, std::string>> tapeA;
    std::list<std::pair<std::string, std::string>> tapeB;

    auto start = std::chrono::high_resolution_clock::now();
    //Load data
    while (getline(filehandle,line)) {
        noOfPairs++;
        std::istringstream ss (line);
        std::string symbol1, symbol2;
        getline(ss, symbol1, ',');
        getline(ss, symbol2);
        ss >> symbol1 >> symbol2;
        tapeA.push_back({symbol1, symbol2});
        tapeB.push_back({symbol1, symbol2});
    }

    //Sort and output timing data
    auto result = sort (tapeA, tapeB);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);

    std::cout << "Number of input pairs: " << noOfPairs << std::endl;
    std::cout << "Nanoseconds taken to load and sort in memory: " << duration.count() << std::endl;

}
