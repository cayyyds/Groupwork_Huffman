#include "huffman.h"
#include <iostream>
#include <fstream>
using namespace std;
// =======================
// 字符频度统计
//赵晨志编写的Stat函数
// =======================
const int CHAR_SET_SIZE = 256;

void Stat(char* s, int* w, int& num) {
   // 清空频度统计
    for(int i = 0; i < CHAR_SET_SIZE; i++) {
        w[i] = 0;
    }
    
    // 读文件统计频度
    ifstream file("f1.txt");
    if(!file) {
        cout << "文件f1.txt打开失败" << endl;
        num = 0;
        return;
    }
    
    char c;
    while(file.get(c)) {
        w[(unsigned char)c]++;
    }
    file.close();
    
    // 提取出现过的字符
    num = 0;
    for(int i = 0; i < CHAR_SET_SIZE; i++) {
        if(w[i] > 0) {
            s[num] = (char)i;
            w[num] = w[i];
            num++;
        }
    }
}

// =======================
// 构建 Huffman 树
// 盛佳一编写构建 Huffman 树函数
// =======================
HuffTree<char>* HuffmanBuild(char* s, int* w, int num) {
    if (num <= 0) return nullptr;
    
    MinHeap<char> heap;
    
    // 第一步：将所有字符作为叶子节点插入最小堆
    for (int i = 0; i < num; i++) {
        HuffNode<char>* leaf = new HuffNode<char>(s[i], w[i]);
        HuffTree<char> tree(leaf);
        heap.insert(tree);
    }
    
    // 第二步：循环合并权重最小的两棵树，构建Huffman树
    while (heap.size > 1) {
        // 取出权重最小的两棵树
        HuffTree<char> t1 = heap.removeFirst();
        HuffTree<char> t2 = heap.removeFirst();
        
        // 创建新的内部节点，权重为两棵子树权重之和
        int combinedWeight = t1.getWeight() + t2.getWeight();
        HuffNode<char>* newNode = new HuffNode<char>(combinedWeight, t1.getRoot(), t2.getRoot());
        
        // 创建新树并插入堆中
        HuffTree<char> newTree(newNode);
        heap.insert(newTree);
    }
    
    // 第三步：返回最终构建好的Huffman树
    HuffTree<char>* result = new HuffTree<char>(heap.data[1].getRoot());
    return result;
}

// =======================
// 生成 Huffman 编码
// 张羿弛编写HuffmanCode，测试得等Huffman节点和树类
// =======================
void HuffmanCode(HuffNode<char>* node, char* code, int len, ofstream& fout) {
   if(node == NULL) return;

   //叶子节点，输出字符、频数、编码
    if(node->left == NULL && node->right == NULL){
        code[len + 1] = '\0';
        fout<< node->data << "\t" << node->weight << "\t" << code << "\n";
        return;
    }

    //处理左子树
    if(node->left != NULL){
        char temp[256];
        strcpy(temp,code);
        temp[len] = '0';
        temp[len+1] = '\0';
        HuffmanCode(node->left,temp,len+1,fout);
    }

    //处理右子树
    if(node->right != NULL){
        char temp[256];
        strcpy(temp,code);
        temp[len] = '1';
        temp[len+1] = '\0';
        HuffmanCode(node->right,temp,len+1,fout);
    }
}

// 刘艺森编写的BuildTreeFromCodeFile函数
// huffman译码：利用 code.txt 中的 “字符 频度 编码” 重建一棵 Huffman 树
HuffTree<char>* BuildTreeFromCodeFile(const string& filename){
    // 1.读取code.txt文件
    map<char, string> codeMap;
    codeMap = loadCodeTable(filename);
    
    // 2.创建root节点
    HuffNode<char>* root = new HuffNode<char>(0, nullptr, nullptr);

    // 3.创建中间节点
    // 对每一个字符编码对进行操作
    for (auto& pair : codeMap) {
        char ch = pair.first;
        string code = pair.second;

        HuffNode<char>* current = root;
        // 对每一个字符从根节点开始往下创建内部节点，到第n-2个bit为止
        for (int i = 0; i < code.length() - 1; i++) {
            if (code[i] == '0') {
                if(current->left == nullptr) {
                    current->left = new HuffNode<char>(0, nullptr, nullptr);
                } else {
                    cout << "ERROR: 此时该节点已经创建过左子树"  << endl;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new HuffNode<char>(0, nullptr,nullptr);
                } else {
                    cout << "ERROR: 此时该节点已经创建过右子树" << endl;
                }
                current = current->right;
            }
        }
        // 创建叶子节点
        if (code.back() == '0') {
            current = new HuffNode<char>(ch, 0);    // 解码时建树不需要频度
        } else {
            current = new HuffNode<char>(ch, 0);
        }
    }

    // 4.返回重建的树
    return new HuffTree<char>(root);
}

//huffman译码：Read实现
void read(unsigned int &bit){

}
