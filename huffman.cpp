#include "Huffman.h"

// =======================
// 字符频度统计
// =======================
void Stat(char* s, int* w, int& num) {
   
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
