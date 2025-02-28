#include "HuffmanTree.h"
#include <fstream>

#define bits 256

unsigned char str2byte(string c);

string byte2str(unsigned char c);

void compress(string filename, int weights[], int kinds);

void decompress(string filename, int kinds);

void writeChar(unsigned char s, ofstream &out);