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
    T data;           // 存储的字符
    int weight;       // 字符频率
    HuffNode<T>* left;
    HuffNode<T>* right;
    // 构造函数
    HuffNode(T d, int w) : data(d), weight(w), left(nullptr), right(nullptr) {}
    HuffNode(int w, HuffNode<T>* l, HuffNode<T>* r) 
        : data(T()), weight(w), left(l), right(r) {}
    // 判断是否为叶子节点
    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
    // 获取权重
    int getWeight() const {
        return weight;
    }
    // 设置左右子节点
    void setLeft(HuffNode<T>* l) { left = l; }
    void setRight(HuffNode<T>* r) { right = r; }
    // 获取左右子节点
    HuffNode<T>* getLeft() const { return left; }
    HuffNode<T>* getRight() const { return right; }
    // 获取数据
    T getData() const { return data; }
};

// -------- Huffman 树 --------
template <typename T>
class HuffTree {
private:
    HuffNode<T>* root;    
public:
    // 构造函数
    HuffTree() : root(nullptr) {}
    HuffTree(HuffNode<T>* r) : root(r) {}
    
    // 析构函数
    ~HuffTree() {
        // clear();
    }
    // 获取根节点
    HuffNode<T>* getRoot() const {
        return root;
    }
    // 设置根节点
    void setRoot(HuffNode<T>* r) {
        root = r;
    }
    // 获取树的权重（根节点的权重）
    int getWeight() const {
        return root != nullptr ? root->getWeight() : 0;
    }
    // 判断树是否为空
    bool isEmpty() const {
        return root == nullptr;
    }
    // 比较运算符重载（用于最小堆）
    bool operator>(const HuffTree<T>& other) const {
        return getWeight() > other.getWeight();
    }
    // 清空树
    void clear() {
        clearRecursive(root);
        root = nullptr;
    }

private:
    // 递归删除树的辅助函数
    void clearRecursive(HuffNode<T>* node) {
        if (node != nullptr) {
            clearRecursive(node->getLeft());
            clearRecursive(node->getRight());
            delete node;
        }
    }
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
        while (i > 1 && data[i].getWeight() < data[i/2].getWeight()) {
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

            if (l <= size && data[l].getWeight() < data[smallest].getWeight())
                smallest = l;
            if (r <= size && data[r].getWeight() < data[smallest].getWeight())
                smallest = r;

            if (smallest == i) break;
            swap(data[i], data[smallest]);
            i = smallest;
        }
        return top;
    }
};

// 赵晨志编写的Buffer结构体框架，刘艺森将其改为Buffer类，
// 修改构造函数并添加一些成员函数（将Write和WriteToOutfp放入）
template <typename T>
class Buffer {
private:
    char ch;    // 缓冲的字节
    unsigned int bits;  // 当前有效的bit数
    FILE* outfp;    // 输出文件指针

    void clear() {ch = 0; bits = 0;}    // clear buffer
    bool isEmpty() const {return bits == 0;}    // check Buffer is empty
    bool isFull() const {return bits == 8;}     // check buffer is full
public:
    // constructor
    Buffer(FILE* fp = nullptr) : ch(0), bits(0), outfp(fp) {}

    // 刘艺森编写的Write函数
    void Write(unsigned int bit){
        ch = ch << 1;
        ch = ch | bit;
        bits++;
        if (isFull()) {
            fputc(ch, outfp);
            clear();
        }
    }

    // 蔡志远编写的WriteToOutfp函数
    void WriteToOutfp() { 
        unsigned int l = bits;
        if (l > 0) {
            for (unsigned int i = 0; i < 8 - l; i++)
                Write(0);
        }
    }
};

// ========== 函数原型 ===========
void Stat(char* s, int* w, int& num);
HuffTree<char>* HuffmanBuild(char* s, int* w, int num);
void HuffmanCode(HuffNode<char>* node, char* code, int len, ofstream& fout);

#endif
