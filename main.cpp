#include "huffman.h"

// 刘艺森编写的char_code函数
void char_code() {
    HuffTree<char>* HuffmanTree;
    int n;
    char *Code;
    char s[NUMBER];
    int w[NUMBER];
    Stat(s, w, n);
    HuffmanTree = HuffmanBuild(s, w, n);
    HuffmanTree->print();
    cout<<endl<<" the coding result is:"<<endl;
    Code = new char[n];
    HuffmanCode(HuffmanTree->root(), Code, -1);
}

void File_Code() {  }
void File_Decode() { }

int main() {
    char option;

    cout << "操作命令说明：" << endl;
    cout << "1:统计并输出字符集+频度集+编码集（基本要求）\n";
    cout << "2:对整个文件编码并生成二进制文件（中级要求）\n";
    cout << "3:解码出原文本（高级要求）\n";
    cout << "4:退出\n";

    do {
        cout << "\n$$ ";
        cin >> option;

        switch (option) {
        case '1':
            char_code();
            break;

        case '2':
            File_Code();
            break;

        case '3':
            File_Decode();
            break;
        }
    } while (option != '4');

    return 0;
}
