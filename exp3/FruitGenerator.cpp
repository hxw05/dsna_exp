//
// Created by 哈哈了 on 2025/4/6.
//

#include "FruitGenerator.h"

FruitGenerator::FruitGenerator(int typeCount) {
    this->types = std::vector<int>(typeCount);
    this->selected = std::vector(typeCount, false);
    this->lastIndex = typeCount - 1;
    std::iota(this->types.begin(), this->types.end(), 0);
}

int FruitGenerator::next() {
    int rand = 0;
    while (selected[rand]) rand = this->types[randInt(0, lastIndex)];
    selected[rand] = true;

    for (const auto &s: selected) {
        if (!s) return rand;
    }

    selected = std::vector(lastIndex + 1, false);
    return rand;
}
