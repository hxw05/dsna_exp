#include "HuffmanTree.h"

pair<int, int> select(HuffmanNode *tree[], int end) {
    int min = 0;
    while (tree[min]->parent != -1) min++;

    for (int i = min; i <= end; i++) {
        if (tree[i]->parent == -1 && tree[i]->weight < tree[min]->weight) {
            min = i;
        }
    }

    int submin = 0;
    while (tree[submin]->parent != -1 || submin == min) submin++;

    for (int i = submin; i <= end; i++) {
        if (i != min && tree[i]->parent == -1 && tree[i]->weight < tree[submin]->weight) {
            submin = i;
        }
    }

    return {min, submin};
}

void buildHuffmanTree(HuffmanNode *tree[], int weights[], int size) {
    // 初始化
    for (int i = 0; i < size; i++) tree[i] = new HuffmanNode(weights[i]);
    for (int i = size; i < size * 2 - 1; i++) tree[i] = new HuffmanNode(0);

    for (int i = size; i < size * 2 - 1; i++) {
        auto targets = select(tree, i - 1);
//
//        printf("merge %d with %d, %d+%d=%d\n", targets.first, targets.second, tree[targets.first]->weight,
//               tree[targets.second]->weight, tree[targets.first]->weight + tree[targets.second]->weight);

        tree[i]->weight = tree[targets.first]->weight + tree[targets.second]->weight;
        tree[i]->lchild = targets.first;
        tree[i]->rchild = targets.second;
        tree[targets.first]->parent = i;
        tree[targets.second]->parent = i;
    }
}

void genHuffmanCode(string code[], HuffmanNode *tree[], int size) {
    for (int i = 0; i < size; i++) {
        string c;
        int current = i;
        int ptr = tree[current]->parent;
//
//        printf("current=%d, ptr=%d, ptr.lchild=%d, ptr.rchild=%d\n", current, ptr, tree[ptr]->lchild, tree[ptr]->rchild);

        while (ptr != -1) {
            if (tree[ptr]->lchild == current) c.insert(0, "0");
            else if (tree[ptr]->rchild == current) c.insert(0, "1");

            current = ptr;
            ptr = tree[ptr]->parent;
        }

        code[i] = c;
    }
}