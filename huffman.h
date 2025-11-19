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
//czy编写
template <typename T>

class MinHeap {
public:
    HuffTree<T> data[NUMBER];
    int size;

    MinHeap() { size = 0; }

    void insert(const HuffTree<T>& t) {
        data[++size] = t;
        int i = size;
        while (i > 1 && data[i].weight() < data[i/2].weight()) {
            swap(data[i], data[i/2]);
            i /= 2;
        }
    }

    HuffTree<T> removeFirst() {
        HuffTree<T> top = data[1];
        data[1] = data[size--];
        int i = 1;

        while (true) {
            int smallest = i;
            int l = 2*i, r = 2*i + 1;

            if (l <= size && data[l].weight() < data[smallest].weight())
                smallest = l;
            if (r <= size && data[r].weight() < data[smallest].weight())
                smallest = r;

            if (smallest == i) break;
            swap(data[i], data[smallest]);
            i = smallest;
        }
        return top;
    }
};



// ========== 函数原型 ===========
void Stat(char* s, int* w, int& num);
HuffTree<char>* HuffmanBuild(char* s, int* w, int num);
void HuffmanCode(HuffNode<char>* node, char* code, int len, ofstream& fout);

#endif
