#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define NUMBER 256   // ASCII 全部字符频度统计

// ------- Huffman 节点 -------
template <typename T>
class HuffNode {
public:

};

// -------- Huffman 树 --------
template <typename T>
class HuffTree {

};

// -------- 最小堆，用于构建 Huffman 树 ----------
template <typename T>
class MinHeap {

};

// ========== 函数原型 ===========
void Stat(char* s, int* w, int& num);
HuffTree<char>* HuffmanBuild(char* s, int* w, int num);
void HuffmanCode(HuffNode<char>* node, char* code, int len, ofstream& fout);

#endif
