#ifndef DSNA_2_EVFILES
#define DSNA_2_EVFILES

#include "global.h"
#include <fstream>

#define EdgeFilePath "/Users/su/CLionProjects/2024-2025-2/dsna_2/edge.txt"
#define VexFilePath "/Users/su/CLionProjects/2024-2025-2/dsna_2/vex.txt"

struct EdgeObject {
    char mark1;
    char mark2;
    int weight;
};

struct VexObject {
    int number;
    char mark;
    string name;
    string desc;
};

vector<EdgeObject> getEdgesFromFile();
vector<VexObject> getVexesFromFile();

#endif