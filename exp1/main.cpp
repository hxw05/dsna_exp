#include <iostream>
#include "Compress.h"

using namespace std;

int main() {
    string filename;
    cout << "====== Huffman 文件压缩 ======" << endl;
    cout << "请输入文件名：";
    cin >> filename;

    ifstream file;
    file.open(filename, ios::binary);
    int filesize = (int) filesystem::file_size(filename);

    cout << "文件大小：" << filesize << "B" << endl;

    int ch;
    int weights[bits] = {0};
    while ((ch = file.get()) != EOF) {
        weights[ch]++;
    }

    file.close();

    compress(filename, weights, bits);
    decompress(filename, bits);
}
