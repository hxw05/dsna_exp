#include "Functions.h"

Graph getGraph() {
    auto es = getEdgesFromFile();
    auto vs = getVexesFromFile();

    return createGraph(vs, es);
}

void showTourismList(Graph &graph) {
    for (int i = 0; i < graph.vexNum; i++) {
        cout << i << "-" << graph.getVexByVexnum(i).name << endl;
    }
}

void fn_InitializeTourism() {
    cout << "===== 创建景区景点图 =====" << endl;

    auto graph = getGraph();

    cout << "顶点数目：" << graph.vexNum << endl;
    cout << "----- 顶点 -----" << endl;
    showTourismList(graph);

    cout << "----- 边 -----" << endl;
    for (int i = 0; i < graph.vexNum; i++) {
        for (int j = 0; j < graph.vexNum; j++) {
            if (graph.matrix[i][j] != 0 && j > i) {
                cout << "<v" << i << ", v" << j << "> " << graph.matrix[i][j] << endl;
            }
        }
    }
}

void fn_QueryTourismInformation() {
    cout << "===== 查询景点信息 =====" << endl;

    auto graph = getGraph();

    showTourismList(graph);

    short choice;

    cin >> choice;

    if (!cin.good() || choice > graph.vexNum || choice < 0) {
        cout << "景区编号无效" << endl;
        reset(cin);
        return;
    }

    Vex v = graph.getVexByVexnum(choice);
    cout << v.name << endl;
    cout << v.desc << endl;

    cout << "----- 周边景区 -----" << endl;

    vector<Vex> adjs = getAdjacentVexes(graph, v);
    for (const auto &adjv: adjs) {
        cout << v.name << "->" << adjv.name << " " << graph.matrix[v.num][adjv.num] << "m" << endl;
    }
}

void fn_DFSTraverseGraph() {
    cout << "===== 旅游景点导航 =====" << endl;

    auto graph = getGraph();

    showTourismList(graph);

    int start;

    cout << "请输入起始点编号：";

    cin >> start;

    if (!cin.good() || start > graph.vexNum || start < 0) {
        cout << "景区编号无效" << endl;
        reset(cin);
        return;
    }

    vector<int> res;
    vector<vector<int>> allPath;
    bool visited[graph.vexNum];

    getPathDFSAll(visited, res, allPath, graph, start);

    cout << "导游路线为：" << endl;
    int cnt = 1;
    for (const auto &p: allPath) {
        cout << "路线" << cnt << "：";
        for (int i = 0; i < p.size(); i++) {
            cout << graph.getVexByVexnum(p[i]).name;
            if (i != p.size() - 1) cout << "->";
        }
        cout << endl;
        cnt++;
    }

    cout << endl;
}

void fn_SearchShortestPath() {
    cout << "===== 搜索最短路径 =====" << endl;

    auto graph = getGraph();

    showTourismList(graph);

    int start, end;

    cout << "请输入起点的编号：";
    cin >> start;
    cout << "请输入终点的编号：";
    cin >> end;

    auto res = Dijkstra(graph, start);

    cout << "从 " << graph.getVexByVexnum(start).name << " 到 " << graph.getVexByVexnum(end).name << endl;
    cout << "最短路线为：";

    vector<int> actualPath;
    int p = end;
    while (p != -1) {
        actualPath.push_back(p);
        p = res.path[p];
    }

    for (int i = actualPath.size() - 1; i >= 0; i--) {
        cout << graph.getVexByVexnum(actualPath[i]).name;
//        if (i != 0) cout << " --" << graph.matrix[actualPath[i]][actualPath[i-1]] << "m--> ";
        if (i != 0) cout << "->";
    }

    cout << endl;
    cout << "最短距离为：" << res.shortestTo[end] << "m" << endl;
}

void fn_CircuitPlanning() {
    cout << "===== 铺设电路规划 =====" << endl;

    auto graph = getGraph();

    vector<Edge> es = PrimAll(graph);

    cout << "在以下两个景点之间铺设电路：" << endl;

    for (const auto &e: es) {
        cout << graph.getVexByVexnum(e.v1).name << " - " << graph.getVexByVexnum(e.v2).name << "  " << e.weight << "m"
             << endl;
    }

    cout << "铺设电路的总长度为：" << SumEdgeWeights(es) << "m" << endl;
}