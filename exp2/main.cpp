#include "global.h"
#include "test.h"
#include "Functions.h"

vector<string> FUNCTIONS = {
        "创建景区景点图",
        "查询景点信息",
        "旅游景点导航",
        "搜索最短路径",
        "铺设电路规划"
};

void reset(istream& in) {
    in.clear();

    in.ignore(INT_MAX, '\n');
}

int main() {
    short choice;

    while (true) {
        cout << "===== 景区信息管理系统 =====" << endl;
        for (int i = 0; i < FUNCTIONS.size(); i++) {
            cout << i + 1 << ". " << FUNCTIONS[i] << endl;
        }
        cout << "0. 退出" << endl;
        cout << "请输入操作编号（0~5）：";
        cin >> choice;

        if (!cin.good()) {
            cout << "操作编号无效" << endl;
            reset(cin);
            continue;
        }

        switch (choice) {
            case 0: return 0;
            case 1: {
                fn_InitializeTourism();
                break;
            }

            case 2: {
                fn_QueryTourismInformation();
                break;
            }

            case 3: {
                fn_DFSTraverseGraph();
                break;
            }

            case 4: {
                fn_SearchShortestPath();
                break;
            }

            case 5: {
                fn_CircuitPlanning();
                break;
            }

            default: {
                cout << "操作编号需在0~5范围内" << endl;
                continue;
            }
        }
    }
}
