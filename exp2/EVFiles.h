#ifndef DSNA_2_EVFILES
#define DSNA_2_EVFILES

#include "global.h"
#include <fstream>

// 修改为绝对路径
#define EdgeFilePath "edge.txt"
#define VexFilePath "vex.txt"

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