#ifndef FRUITGENERATOR_H
#define FRUITGENERATOR_H

#include "utils.h"

class FruitGenerator {

public:
    std::vector<int> types;
    std::vector<bool> selected;
    int lastIndex;

    FruitGenerator(int typeCount);

    int next();
};



#endif //FRUITGENERATOR_H
