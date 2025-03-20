#include "EVFiles.h"
#include "test.h"
#include "Graph.h"

void test_FileReading() {
    auto res1 = getEdgesFromFile();
    auto res2 = getVexesFromFile();

    for (auto r1: res1) {
        printf("%c %c %d\n", r1.mark1, r1.mark2, r1.weight);
    }

    cout << "---" << endl;

    for (auto r2: res2) {
        printf("%d %c %s %s\n", r2.number, r2.mark, r2.name.c_str(), r2.desc.c_str());
    }
}

void test_Graph() {
    auto res1 = getEdgesFromFile();
    auto res2 = getVexesFromFile();

    auto graph = createGraph(res2, res1);

    cout << "顶点数目：" << graph.vexNum << endl;
    cout << "---- 顶点 ----" << endl;
    for (int i = 0; i < graph.vexNum; i++) {
        cout << i << "-" << graph.getVexByVexnum(i).name << endl;
    }

    cout << "---- 边 ----" << endl;
    for (int i = 0; i < MaxVexIndex; i++) {
        for (int j = 0; j < MaxVexIndex; j++) {
            if (graph.matrix[i][j] != 0) {
                cout << "<v" << i << ", v" << j << "> " << graph.matrix[i][j] << endl;
            }
        }
    }
}

void test_DFS() {
    auto res1 = getEdgesFromFile();
    auto res2 = getVexesFromFile();

    auto graph = createGraph(res2, res1);


    printf("--------------dfs_a:\n");
    bool visited1[100][graph.vexNum];
    for (int i = 0; i < graph.vexNum; i++) {
        vector<int> r1;
        vector<vector<int>> r2;

        printf("start from %d\n", i);

        getPathDFSAll(visited1[i], r1, r2, graph, i);

        printf("verification:\n");

        for (const auto &p: r2) {
            bool flag = false;
            for (int i = 0; i < p.size() - 1; i++) {
                if (graph.matrix[p[i]][p[i + 1]] == 0) {
                    flag = true;
                    break;
                }
            }

            cout << (flag ? "failed" : "passed") << endl;
        }

        for (const auto &p: r2) {
            for (const auto &v: p) {
                cout << graph.getVexByVexnum(v).name << " ";
            }

            cout << endl;
        }
    }
    printf("--------------dfs:\n");
    bool visited2[100][graph.vexNum];
    for (int i = 0; i < graph.vexNum; i++) {
        vector<int> r{};

        printf("start from %d\n", i);

        getPathDFS(visited2[i], r, graph, i);

        bool flag = false;
        for (int i = 0; i < r.size() - 1; i++) {
            if (graph.matrix[r[i]][r[i + 1]] == 0) {
                flag = true;
                break;
            }
        }

        cout << (flag ? "failed" : "passed") << endl;

        for (const auto &v: r) {
            cout << graph.getVexByVexnum(v).name << " ";
        }
        cout << endl;
    }
}

void test_Dijkstra() {
    auto res1 = getEdgesFromFile();
    auto res2 = getVexesFromFile();

    auto graph = createGraph(res2, res1);

    int v0 = 0;

    auto res = Dijkstra(graph, v0);

    for (int i = 0; i < res.shortestTo.size(); i++) {
        cout << "from " << v0 << ": shortest to " << i << ": " << res.shortestTo[i] << endl;
    }
}

void test_Prim() {
    auto res1 = getEdgesFromFile();
    auto res2 = getVexesFromFile();

    auto graph = createGraph(res2, res1);

    int v0 = 0;

    auto res = Prim(graph, v0);

    for (const auto &e: res) {
        cout << "v1: " << e.v1 << ", v2: " << e.v2 << ", cost: " << e.weight << endl;
    }
}