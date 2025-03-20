#include "Graph.h"
#include "EVFiles.h"

Graph createGraph(const vector<VexObject> &vs, const vector<EdgeObject> &es) {
    Graph g{};

    for (auto &v: vs) {
        g.mark2number[v.mark] = v.number;
        g.InsertVex({v.number, v.name, v.desc});
    }

    for (auto &e: es) {
        g.InsertEdge({g.getNumberByMark(e.mark1), g.getNumberByMark(e.mark2), e.weight});
    }

    return g;
}

vector<Vex> getAdjacentVexes(const Graph &g, const Vex &from) {
    vector<Vex> res;

    for (int j = 0; j < g.vexNum; j++) {
        if (g.matrix[from.num][j] != 0) {
            res.push_back(g.vexes[j]);
        }
    }

    return res;
}

void getPathDFSAll(bool *visited, vector<int> &res, vector<vector<int>> &allPath, const Graph &g, int start) {
    res.push_back(start);
    visited[start] = true;

    for (int n = 0; n < g.vexNum; n++) {
        if (g.matrix[start][n] != 0 && !visited[n]) {
            getPathDFSAll(visited, res, allPath, g, n);
        }
    }

    // 对于连通图
    if (res.size() == g.vexNum) {
        allPath.push_back(res);
    }

    res.pop_back();
    visited[start] = false;
}

void getPathDFS(bool *visited, vector<int> &res, const Graph &g, int start) {
    res.push_back(start);
    visited[start] = true;

    for (int n = 0; n < g.vexNum; n++) {
        if (g.matrix[start][n] != 0 && !visited[n]) {
            getPathDFS(visited, res, g, n);
        }
    }
}

int DijkstraNormalize(int x) {
    return x > 0 ? x : DijkstraInfinity;
}

DijkstraResult Dijkstra(Graph &g, int v0) {
    DijkstraResult res;

    bool determined[g.vexNum]; // S
    vector<int> shortestTo(g.vexNum); // D
    vector<int> path(g.vexNum); // Path

    path[v0] = -1;

    for (int i = 0; i < g.vexNum; i++) {
        shortestTo[i] = DijkstraNormalize(g.matrix[v0][i]);

        if (shortestTo[i] < DijkstraInfinity) path[i] = v0;
        else path[i] = -1;
    }

    determined[v0] = true;
    shortestTo[v0] = 0;

    for (int i = 1; i < g.vexNum; i++) {
        int minLen = DijkstraInfinity;
        int v;

        for (int w = 0; w < g.vexNum; w++) {
            if (!determined[w] && shortestTo[w] < minLen) {
                v = w;
                minLen = shortestTo[w];
            }
        }

//        cout << "found minlen on " << v << ": " << minLen << endl;

        determined[v] = true;

        for (int w = 0; w < g.vexNum; w++) {
            if (determined[w]) continue;
            int supposed = shortestTo[v] + DijkstraNormalize(g.matrix[v][w]);
//            cout << "v: " << v << ", w: " << w << "; supposed: " << supposed << "; shortestTo[" << w << "]: " << shortestTo[w] << endl;
            if (supposed < shortestTo[w]) {
                shortestTo[w] = supposed;
                path[w] = v;
            }
        }
    }

    res.shortestTo = shortestTo;
    res.path = path;
    return res;
}

vector<Edge> Prim(Graph &g, int v0) {
    PrimEdge adjEdge[g.vexNum];
    vector<Edge> edges;
    bool determined[g.vexNum];

    for (int i = 0; i < g.vexNum; i++) {
        if (i != v0) {
            adjEdge[i] = {DijkstraNormalize(g.matrix[v0][i]), v0};
        }
    }

    adjEdge[v0].cost = 0;
    determined[v0] = true;

    for (int i = 1; i < g.vexNum; i++) {
        int minTargetVex = 0;
        while (determined[minTargetVex]) minTargetVex++;
//        cout << "start from " << minTargetVex << endl;
        for (int j = 0; j < g.vexNum; j++) {
//            cout << determined[j] << ": " << adjEdge[j].cost << " ~ " << adjEdge[minTargetVex].cost << endl;
            if (adjEdge[j].cost < adjEdge[minTargetVex].cost && !determined[j]) {
                minTargetVex = j;
            }
        }

        edges.push_back({adjEdge[minTargetVex].source, minTargetVex, adjEdge[minTargetVex].cost});

        adjEdge[minTargetVex].cost = 0;
        determined[minTargetVex] = true;
//        cout << "determined " << minTargetVex << endl;

        for (int j = 0; j < g.vexNum; j++) {
            if (DijkstraNormalize(g.matrix[minTargetVex][j]) < adjEdge[j].cost) {
                adjEdge[j] = {DijkstraNormalize(g.matrix[minTargetVex][j]), minTargetVex};
            }
        }
    }

    return edges;
}

int SumEdgeWeights(const vector<Edge>& es) {
    int sum = 0;
    for (const auto &e: es)sum += e.weight;
    return sum;
}

vector<Edge> PrimAll(Graph &g) {
    int minCost = 99999;
    vector<Edge> res;

    for (int i = 0; i < g.vexNum; i++) {
        vector<Edge> r = Prim(g, i);
        int sum = SumEdgeWeights(r);

        if (sum < minCost) {
            minCost = sum;
            res = r;
        }
    }

    return res;
}
