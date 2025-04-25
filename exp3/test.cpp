#include "test.h"
#include <iostream>
#include <numeric>
#include <random>
#include <fstream>
#include <QTime>
#include <vector>

#include "RecordManager.h"

using namespace std;

struct genmap_result {
    vector<int> original;
    vector<int> downgraded;
    double original_rate;
    double downgraded_rate;
};

template<typename T>
void shuffle2(std::vector<T> &arr) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
}

bool isNeighbor2(int p1, int p2, int width) {
    int x1 = p1 % width, y1 = p1 / width;
    int x2 = p2 % width, y2 = p2 / width;

    // 水平或者竖直
    return (abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2);
}

int randInt2(int start, int end) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(start, end);
    return distribution(generator);
}

vector<pair<int, int> > getNeighbors2(const std::vector<int> &arr, int width, int height) {
    vector<pair<int, int> > neighbors;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int pos = j * width + i;

            if (i < width - 1)
                if (arr[pos] == arr[pos + 1]) {
                    neighbors.emplace_back(pos, pos + 1);
                }
            if (j < height - 1)
                if (arr[pos] == arr[pos + width]) {
                    neighbors.emplace_back(pos, pos + width);
                }
        }
    }

    return neighbors;
}

genmap_result genMap2(int width, int height, int fruitTypeCount, double neighborRate,
                      std::vector<std::string> &flags, int maxIteration) {
    std::vector fruitMap(width * height, -1);

    const int totalPairCount = fruitMap.size() / 2;
    const int targetNeighborPairCount = std::round(totalPairCount * neighborRate);

    std::vector<std::pair<int, int> > adjSlots;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int pos = y * width + x;

            if (x < width - 1) adjSlots.emplace_back(pos, pos + 1);
            if (y < height - 1) adjSlots.emplace_back(pos, pos + width);
        }
    }

    shuffle2(adjSlots);

    std::vector isSlotOccupied(fruitMap.size(), false);

    std::vector isAdjacentPair(totalPairCount, false);
    std::vector<int> pairId(totalPairCount);

    std::iota(pairId.begin(), pairId.end(), 0);

    shuffle2(pairId);

    for (int i = 0; i < targetNeighborPairCount; i++) {
        isAdjacentPair[pairId[i]] = true;
    }

    for (int p = 0; p < totalPairCount; p++) {
        if (isAdjacentPair[p]) {
            int fruitType = randInt2(0, fruitTypeCount - 1);
            bool placed = false;

            for (const auto &[first, second]: adjSlots) {
                if (!isSlotOccupied[first] && !isSlotOccupied[second]) {
                    isSlotOccupied[first] = isSlotOccupied[second] = true;
                    flags[first] = flags[second] = "1@" + std::to_string(p);
                    fruitMap[first] = fruitMap[second] = fruitType;
                    placed = true;
                    break;
                }
            }

            if (!placed) {
                isAdjacentPair[p] = false;
            }
        }
    }

    std::vector<int> freePositions;
    for (int i = 0; i < isSlotOccupied.size(); i++) {
        if (!isSlotOccupied[i]) freePositions.push_back(i);
    }

    if (freePositions.size() % 2 != 0) throw "FreePositions must be odd";

    shuffle2(freePositions);

    for (int p = 0; p < totalPairCount; p++) {
        if (!isAdjacentPair[p]) {
            int fruitType = randInt2(0, fruitTypeCount - 1);
            bool placed = false;

            for (int i = 0; i < freePositions.size() && !placed; i++) {
                for (int j = i + 1; j < freePositions.size(); j++) {
                    if (!isNeighbor2(freePositions[i], freePositions[j], width)) {
                        flags[freePositions[i]] = flags[freePositions[j]] = "2@" + std::to_string(p);
                        fruitMap[freePositions[i]] = fruitMap[freePositions[j]] = fruitType;
                        freePositions.erase(freePositions.begin() + i);
                        freePositions.erase(freePositions.begin() + j - 1); // j > i
                        placed = true;
                        break;
                    }
                }
            }

            if (!placed && freePositions.size() >= 2) {
                fruitMap[freePositions[0]] = fruitType;
                fruitMap[freePositions[1]] = fruitType;
                freePositions.erase(freePositions.begin());
                freePositions.erase(freePositions.begin());
            }
        }
    }

    auto fruitMapOriginal = fruitMap;

    auto endingNeighbors = getNeighbors2(fruitMap, width, height);
    int outerLoops = 0;
    double endingNeighborRate = 2.0 * endingNeighbors.size() / fruitMap.size();

    auto originalRate = endingNeighborRate;

    // cout << "after process ending rate: " << endingNeighborRate << endl;

    while ((endingNeighborRate = 2.0 * getNeighbors2(fruitMap, width, height).size() / fruitMap.size()) > neighborRate
           &&
           endingNeighbors.size() > 1) {
        outerLoops++;

        if (outerLoops - 1 == maxIteration) {
            // cout << "break " << maxIteration << endl;
            break;
        }

        int n1 = randInt2(0, endingNeighbors.size() - 1);
        int target1 = randInt2(0, 1) ? endingNeighbors[n1].first : endingNeighbors[n1].second;

        int innerLoops = 0;

        while (true) {
            innerLoops++;

            if (innerLoops - 1 == maxIteration) {
                // cout << "inner break " << maxIteration << endl;
                break;
            }

            int n2 = n1;
            while (n2 == n1) n2 = randInt2(0, endingNeighbors.size() - 1);
            int target2 = randInt2(0, 1) ? endingNeighbors[n2].first : endingNeighbors[n2].second;

            if (fruitMap[target1] == fruitMap[target2]) continue;
            std::swap(fruitMap[target1], fruitMap[target2]);

            std::erase(endingNeighbors, endingNeighbors[n1]);
            std::erase(endingNeighbors, endingNeighbors[n2]);
            break;
        }
    }

    // cout << "resulting rate: " << endingNeighborRate << endl;

    return {fruitMapOriginal, fruitMap, originalRate, endingNeighborRate};
}


void test() {
    int width = 16;
    int height = 10;

    auto rates = std::vector<double>{0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    auto iterations = std::vector<int>{50, 100, 200, 500, 1000};

    std::vector<string> flags(width * height);

    for (const auto &rate: rates) {
        std::vector<double> deltaAvgs;
        ofstream testoutput("map-rates." + std::to_string(rate) + ".txt");
        for (const auto &it: iterations) {
            testoutput << "it=" << it << endl << endl;
            double deltaSum = 0;

            for (int i = 0; i < 50; i++) {
                auto res = genMap2(width, height, 10, rate, flags, it);
                // cout << deltaSum << " + " << abs(res.downgraded_rate - res.original_rate) << " = " << deltaSum +abs(res.downgraded_rate - res.original_rate)<< endl;
                deltaSum += abs(res.downgraded_rate - res.original_rate);
                testoutput << "original: " << res.original_rate << ", downgraded: " << res.downgraded_rate << ", delta: " << abs(res.
                        downgraded_rate - res.original_rate) << endl;
            }

            // cout << deltaSum << "/ 50 = " << deltaSum / 50 << endl;

            deltaAvgs.push_back(deltaSum / 50);

            testoutput << endl << endl;
        }

        for (int i =0; i < deltaAvgs.size(); i++) {
            testoutput << "it: " << iterations[i] << ", delta_avg: " << deltaAvgs[i] << endl;
        }

        testoutput.flush();
        testoutput.close();
    }

    for (const auto &rate: rates) {
        ofstream testoutput("map." + std::to_string(rate) + ".txt");
        auto res = genMap2(width, height, 10, rate, flags, 1000);

        testoutput << endl;
        testoutput << "original: " << res.original_rate << endl << endl;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                // testoutput << res[width * j + i] << "-" << flags[width * j + i] << " ";
                testoutput << res.original[width * j + i] << " ";
            }

            testoutput << endl;
        }

        testoutput << endl;
        testoutput << "downgraded: " << res.downgraded_rate << endl << endl;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                // testoutput << res[width * j + i] << "-" << flags[width * j + i] << " ";
                testoutput << res.downgraded[width * j + i] << " ";
            }

            testoutput << endl;
        }

        testoutput.flush();
        testoutput.close();
    }
}

void test_records() {
    auto manager = RecordManager("records-test.txt");
    manager.addRecord({"q", 7, 8, 9});
    auto records = manager.getRecords();

    for (const auto &it: records) {
        cout << it.name << it.mode << it.time << it.finishedAt << endl;
    }
}
