#include "global.h"
#include "EVFiles.h"

#define GraphWidth 20
#define MaxVexes GraphWidth
#define MinVexIndex 0
#define MaxVexIndex (MaxVexes - 1)
#define DijkstraInfinity 9999

struct Vex {
    int num;
    string name;
    string desc;
};

struct Edge {
    int v1;
    int v2;
    int weight;
};

class Graph {
public:
    int matrix[GraphWidth][GraphWidth]{0};
    Vex vexes[GraphWidth];
    int vexNum = 0;
    int mark2number[MaxVexes];

    Graph() = default;

    Vex getVexByVexnum(int vexnum) {
        return vexes[vexnum];
    }

    int getNumberByMark(char mark) {
        return mark2number[mark];
    }

    bool InsertVex(Vex v) {
        if (vexNum == MaxVexes) {
            return false;
        }

        vexes[vexNum++] = v;
        return true;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArrayIndexOutOfBounds"

    bool InsertEdge(Edge e) {
        if (e.v1<MinVexIndex || e.v1>MaxVexIndex || e.v2<MinVexIndex || e.v2>MaxVexIndex) {
            return false;
        }

        matrix[e.v1][e.v2] = e.weight;
        matrix[e.v2][e.v1] = e.weight;
        return true;
    }

#pragma clang diagnostic pop
};

struct DijkstraResult {
    vector<int> shortestTo;
    vector<int> path;
};

struct PrimEdge {
    int cost;
    int source;
};

Graph createGraph(const vector<VexObject> &vs, const vector<EdgeObject> &es);
vector<Vex> getAdjacentVexes(const Graph& g, const Vex& from);
void getPathDFSAll(bool* visited, vector<int>& res, vector<vector<int>>& allPath, const Graph& g, int start);
void getPathDFS(bool* visited, vector<int>& res, const Graph& g, int start);
DijkstraResult Dijkstra(Graph &g, int v0);
vector<Edge> PrimAll(Graph &g);
vector<Edge> Prim(Graph &g, int v0);
int SumEdgeWeights(const vector<Edge>& es);