#include "Huffman.h"
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
// =======================
HuffTree<char>* HuffmanBuild(char* s, int* w, int num) {
   
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
        fout<< node->val << "\t" << node->weight << "\t" << code <<endl;
        return;
    }

    //处理左子树
    if(node->left != NULL){
        char temp[256];
        strcpy(temp,code);
        int llen = len + 1;
        temp[llen] = '0';
        temp[llen+1] = '\0';
        HuffmanCode(node->left,temp,llen,fout);
    }

    //处理右子树
    if(node->right != NULL){
        char temp[256];
        strcpy(temp,code);
        int rlen = len + 1;
        temp[rlen] = '1';
        temp[rlen+1] = '\0';
        HuffmanCode(node->right,temp,rlen,fout);
    }
}
