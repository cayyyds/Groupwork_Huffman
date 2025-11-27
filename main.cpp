#include "huffman.h"
#include <clocale>

// 刘艺森编写的char_code函数
void char_code() {
    HuffTree<char>* HuffmanTree;
    int n;
    char *Code;
    char s[NUMBER];
    int w[NUMBER];
    Stat(s, w, n);
    
    // 检查是否成功读取文件
    if (n <= 0) {
        cout << "ERROR:无法读取文件或文件为空" << endl;
        return;
    }
    
    HuffmanTree = HuffmanBuild(s, w, n);
    
    // 检查是否成功构建Huffman树
    if (HuffmanTree == nullptr || HuffmanTree->getRoot() == nullptr) {
        cout << "ERROR:构建Huffman树失败" << endl;
        return;
    }
    
    Code = new char[n];
    ofstream fout("code.txt");
    
    // 检查文件是否成功打开
    if (!fout) {
        cout << "ERROR:无法创建输出文件 code.txt" << endl;
        return;
    }
    
    HuffmanCode(HuffmanTree->getRoot(), Code, 0, fout);
    fout.close();
    
    // 编码成功，打印输出文件名称
    cout << "Successful! the coding result is: code.txt" << endl;
}

void File_Code() {  }
void File_Decode() { }

int main() {
    setlocale(LC_ALL, "zh_CN.UTF-8");
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
