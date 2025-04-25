#include "utils.h"

#include "FruitGenerator.h"

void setBackground(QWidget *window, const char *filename) {
    auto background = getBackground(window, filename);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    window->setPalette(palette);
}

QPixmap getBackground(QWidget *window, const char *filename) {
    QPixmap background(filename);
    background = background.scaled(window->size(), Qt::IgnoreAspectRatio);
    return background;
}

int randInt(int start, int end) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(start, end);
    return distribution(generator);
}

template<typename T>
void shuffle(std::vector<T> &arr) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
}

bool isNeighbor(int p1, int p2, int width) {
    int x1 = p1 % width, y1 = p1 / width;
    int x2 = p2 % width, y2 = p2 / width;

    // 水平或者竖直
    return (abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2);
}

std::vector<std::pair<int, int> > getNeighbors(const std::vector<int> &arr, int width, int height) {
    std::vector<std::pair<int, int> > neighbors;

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

GenMapResult genMap(int width, int height, int fruitTypeCount, double neighborRate) {
    std::vector fruitMap(width * height, -1);
    FruitGenerator fruitGen(fruitTypeCount);

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

    shuffle(adjSlots);

    std::vector isSlotOccupied(fruitMap.size(), false);

    std::vector isAdjacentPair(totalPairCount, false);
    std::vector<int> pairId(totalPairCount);

    std::iota(pairId.begin(), pairId.end(), 0);

    shuffle(pairId);

    for (int i = 0; i < targetNeighborPairCount; i++) {
        isAdjacentPair[pairId[i]] = true;
    }

    for (int p = 0; p < totalPairCount; p++) {
        if (isAdjacentPair[p]) {
            int fruitType = fruitGen.next();
            bool placed = false;

            for (const auto &[first, second]: adjSlots) {
                if (!isSlotOccupied[first] && !isSlotOccupied[second]) {
                    isSlotOccupied[first] = isSlotOccupied[second] = true;
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

    if (freePositions.size() % 2 != 0) throw "FreePositions must be even";

    shuffle(freePositions);

    for (int p = 0; p < totalPairCount; p++) {
        if (!isAdjacentPair[p]) {
            int fruitType = fruitGen.next();
            bool placed = false;

            for (int i = 0; i < freePositions.size() && !placed; i++) {
                for (int j = i + 1; j < freePositions.size(); j++) {
                    if (!isNeighbor(freePositions[i], freePositions[j], width)) {
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

    auto endingNeighbors = getNeighbors(fruitMap, width, height);
    int outerLoops = 0;
    double endingNeighborRate;

    while ((endingNeighborRate = 2.0 * getNeighbors(fruitMap, width, height).size() / fruitMap.size()) > neighborRate &&
           endingNeighbors.size() > 1) {
        outerLoops++;

        if (outerLoops - 1 == 500) {
            break;
        }

        int n1 = randInt(0, endingNeighbors.size() - 1);
        int target1 = randInt(0, 1) ? endingNeighbors[n1].first : endingNeighbors[n1].second;

        int innerLoops = 0;

        while (true) {
            innerLoops++;

            if (innerLoops - 1 == 500) break;

            int n2 = n1;
            while (n2 == n1) n2 = randInt(0, endingNeighbors.size() - 1);
            int target2 = randInt(0, 1) ? endingNeighbors[n2].first : endingNeighbors[n2].second;

            if (fruitMap[target1] == fruitMap[target2]) continue;
            std::swap(fruitMap[target1], fruitMap[target2]);

            std::erase(endingNeighbors, endingNeighbors[n1]);
            std::erase(endingNeighbors, endingNeighbors[n2]);
            break;
        }
    }

    return {
        fruitMap,
        endingNeighborRate
    };
}