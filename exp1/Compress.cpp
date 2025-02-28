#include "Compress.h"
#include "iostream"

unsigned char str2byte(string s) {
    while (s.size() < 8) s += "0";
    return (unsigned char) stoi(s, nullptr, 2);
}

string byte2str(unsigned char s) {
    return bitset<8>(s).to_string();
}

void writeChar(unsigned char s, ofstream &out) {
    unsigned char cc[1];
    cc[0] = s;
    out.write(reinterpret_cast<const char *>(cc), sizeof(cc));
}

void compress(string filename, int weights[], int kinds) {
    HuffmanNode *tree[kinds * 2];
    buildHuffmanTree(tree, weights, kinds);

    string code[kinds];
    genHuffmanCode(code, tree, kinds);

    ofstream out;
    ifstream in;
    in.open(filename, ios::binary);
    out.open(filename + ".buf", ios::binary);

    int cursor = 0;
    int compressed_size = 0;
    int ch;
    string code_raw;

    while ((ch = in.get()) != EOF) {
        code_raw += code[ch];
    }

    cout << "raw bitstream size:" << code_raw.size() << endl;

    in.close();

    for (int i = 0; i < kinds; i++) {
        out << weights[i] << " ";
    }

    int len = (int) code_raw.length();

    out << len << "\n";

    while (cursor < len) {
        int substrLen = min(8, len - cursor);
        string sub = code_raw.substr(cursor, substrLen);
        writeChar(str2byte(sub), out);
        cout << sub << "->" << (int) str2byte(sub) << endl;
        compressed_size += sizeof(unsigned char);
        cursor += 8;
    }

    cout << "压缩文件大小：" << compressed_size << "B" << endl;

    out.close();
}

void decompress(string filename, int kinds) {
    ifstream in;
    ofstream out;
    in.open(filename + ".buf", ios::binary);
    out.open(filename + ".dec.bmp", ios::binary);

    int weights[kinds];
    int bitstream_length;

    for (int i = 0; i < kinds; i++) {
        in >> weights[i];
    }

    in >> bitstream_length;

    in.get();

    HuffmanNode *tree[kinds * 2];
    buildHuffmanTree(tree, weights, kinds);

    unsigned char ch;
    string bitStream;

    while (in.read(reinterpret_cast<char *>(&ch), 1)) {
        bitStream += byte2str(ch);
        cout << (int) ch << "->" << byte2str(ch) << endl;
    }

    cout << "output bitstream size:" << bitStream.size() << endl;

    if (bitStream.size() > bitstream_length) bitStream = bitStream.substr(0, bitstream_length);

    in.close();

    int ptr = kinds * 2 - 2;
    int decompressed_size = 0;

    for (char bit: bitStream) {
        ptr = bit == '0' ? tree[ptr]->lchild : tree[ptr]->rchild;

        if (tree[ptr]->lchild == -1 && tree[ptr]->rchild == -1) {
            writeChar((unsigned char) ptr, out);
            decompressed_size++;
            ptr = kinds * 2 - 2;
        }
    }

    cout << "解压缩文件大小：" << decompressed_size << "B" << endl;

    out.close();
}