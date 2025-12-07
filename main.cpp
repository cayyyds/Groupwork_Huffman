#include "huffman.h"
#include <clocale>
#include <map>
#include <string>

void Write(unsigned int bit);
void WriteToOutfp();
map<char,string> loadCodeTable(const string& filename);

// 盛佳一编写加载码表函数，从code.txt文件中读取字符与其对应的Huffman编码
map<char,string> loadCodeTable(const string& filename) {
    map<char,string> codeTable;
    ifstream fin(filename);
    
    if (!fin) {
        cout << "ERROR: 无法打开文件 " << filename << endl;
        return codeTable;
    }
    
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        
        // 格式: 字符\t频度\t编码
        // 提取字符（第一个字符）
        char ch = line[0];
        
        // 找到最后一个Tab，后面的内容就是编码
        size_t lastTab = line.rfind('\t');
        if (lastTab != string::npos && lastTab + 1 < line.length()) {
            string code = line.substr(lastTab + 1);
            codeTable[ch] = code;
        }
    }
    
    fin.close();
    return codeTable;
}

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
// 张羿弛编写的File_Code函数
void File_Code()
{
    // 读取码表
    map<char,string> codeTable = loadCodeTable("code.txt");
    if (codeTable.empty()) {
        cout << "ERROR: 请先执行选项 1\n";
        return;
    }

    // 打开原文件
    ifstream fin("f1.txt", ios::binary);
    if (!fin) {
        cout << "ERROR: 无法打开原文件 f1.txt\n";
        return;
    }

    // 打开输出文件
    FILE* fp = fopen("f1_result.huf", "wb");
    if (!fp) {
        cout << "ERROR: 无法创建输出文件 f1_result.huf\n";
        return;
    }

    Buffer<unsigned char> buf(fp);

    unsigned long long origin_bits = 0;
    unsigned long long coded_bits = 0;

    char ch;
    while (fin.get(ch)) {
        string code = codeTable[ch];
        origin_bits += 8;              // 原字符 = 8 bit
        coded_bits  += code.length();  // Huffman 编码位数

        // 写 bit
        for (char bit : code) {
            buf.Write(bit == '1');
        }
    }

    // 写入最后不足 8 bit 的缓冲
    buf.WriteToOutfp();

    fclose(fp);
    fin.close();

    cout << "编码完成！输出文件:f1_result.huf\n";
    cout << "原文件大小：" << origin_bits/8 << " bytes\n";
    cout << "编码后:" << coded_bits/8.0 << " bytes\n";
    cout << "压缩比 = " << (double)coded_bits / origin_bits << endl;
}

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


