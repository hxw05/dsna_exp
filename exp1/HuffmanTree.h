#include <utility>
#include <string>

using namespace std;

class HuffmanNode {
public:
    int weight;
    int parent;
    int lchild;
    int rchild;

    explicit HuffmanNode(int w) : weight(w), parent(-1), lchild(-1), rchild(-1) {};
};

pair<int, int> select(HuffmanNode* tree[], int size);
void buildHuffmanTree(HuffmanNode** tree, int weights[], int size);
void genHuffmanCode(string code[], HuffmanNode **tree, int size);