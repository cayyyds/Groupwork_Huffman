#include "huffman.h"
#include <iostream>
#include <fstream>

int main() {
    std::cout << "=== Huffman Coder Complete Test ===\n" << std::endl;
    
    // 1. Create test file
    std::ofstream fout("f1.txt");
    fout << "hello world";
    fout.close();
    std::cout << "1. Created test file f1.txt" << std::endl;
    
    // 2. Test character statistics
    char s[NUMBER];
    int w[NUMBER];
    int num = 0;
    Stat(s, w, num);
    std::cout << "2. Found " << num << " different characters" << std::endl;
    
    // 3. Test building Huffman tree
    HuffTree<char>* tree = HuffmanBuild(s, w, num);
    if(!tree || !tree->getRoot()) {
        std::cout << "ERROR: Failed to build Huffman tree!" << std::endl;
        return 1;
    }
    std::cout << "3. Built Huffman tree successfully" << std::endl;
    std::cout << "   Tree weight: " << tree->getWeight() << std::endl;
    
    // 4. Test generating code table
    char code[NUMBER];
    std::ofstream code_out("code.txt");
    HuffmanCode(tree->getRoot(), code, 0, code_out);
    code_out.close();
    std::cout << "4. Generated code table: code.txt" << std::endl;
    
    // Show code table
    std::ifstream code_in("code.txt");
    std::cout << "Code table content:" << std::endl;
    std::string line;
    while(std::getline(code_in, line)) {
        std::cout << "  " << line << std::endl;
    }
    code_in.close();
    
    delete tree;
    
    std::cout << "\nTest completed successfully!" << std::endl;
    return 0;
}