# PROJECT2 — A SIMPLE HUFFMAN CODER
## 基于 Huffman 树的文本压缩与解压系统
### 四川大学 数据结构 Project2

---

# 1. 项目简介（Overview）

本项目实现一个 **简易的 Huffman 文本编码器**，用于对英文文本文件进行压缩与解压。程序分为三个主功能：

| 功能       | 分值 | 描述 |
|-----------|------|------|
| 基本要求 | 40 分 | 字符频度统计、构建 Huffman 树、生成并输出字符编码表 |
| 中级要求 | 45 分 | 使用 Huffman 编码对整个文本按 bit 编码，输出二进制文件 |
| 高级要求 | 50 分 | 读取二进制文件，按 Huffman 树解码还原原始文本 |

当前版本已实现 **基本要求（字符统计 + Huffman 编码）**，其他两个功能预留接口。

---

# 2. 项目目录结构（Project Structure）

```
PROJECT2/
│
├── main.cpp               # 主程序，包含 UI 菜单与用户输入控制
├── Huffman.h              # Huffman 节点、树与最小堆结构定义
├── Huffman.cpp            # Huffman 具体实现：统计、建树、编码
│
├── f1.txt                 # 输入文本（待压缩）
├── f1_code.txt            # 基本要求输出：字符-频度-编码表
│
└── PROJECT2_HuffmanCoder.md   # 本项目说明文档（你当前阅读的）
```

---

# 3. 功能模块说明（Module Description）

## 3.1 `main.cpp` —— 主控制模块
负责与用户交互，显示菜单，根据指令调用：

- `char_code()` —— 完成基本要求：统计字符 + 构建Huffman树 + 输出编码表  
- `File_Code()` —— 中级要求：对整个文件编码（待实现）  
- `File_Decode()` —— 高级要求：解码文件（待实现）

### 主菜单结构
```
1：统计并输出字符集+频度集+编码集（基本要求）
2：对整个文件编码并生成二进制文件（中级要求）
3：解码出原文本（高级要求）
4：退出
```

---

## 3.2 `Huffman.h` —— 数据结构定义模块

### 内容包括：
- `HuffNode<T>`：Huffman 树结点（字符、频度、左右子树）
- `HuffTree<T>`：Huffman 树本体（包含建树与打印）
- `MinHeap<T>`：最小堆（用于选出最小两个权值构造 Huffman 树）

### 公开函数接口：
```cpp
void Stat(char* s, int* w, int& num);
HuffTree<char>* HuffmanBuild(char* s, int* w, int num);
void HuffmanCode(HuffNode<char>* node, char* code, int len, ofstream& fout);
```

---

## 3.3 `Huffman.cpp` —— 算法实现模块

包含完整 Huffman 算法流程：

1. **Stat()** —— 统计字符频度  
   - 输入: `f1.txt`  
   - 输出: 字符集 `s[]`、频度集 `w[]`、字符数量 `num`

2. **HuffmanBuild()** —— 利用最小堆构建 Huffman 树  
   - 每次取出两个最小频度的树进行合并  
   - 直到剩下唯一根节点

3. **HuffmanCode()** —— 从 Huffman 树根节点开始递归生成码字  
   - 左子树 → 0  
   - 右子树 → 1  
   - 输出格式存入 `f1_code.txt`：

```
Character  Frequency  Code
a 21 010
b 13 0110
c 7 1101
...
```

---

# 4. 数据流程图（Data Flowchart）

## 4.1 基本要求：字符统计 + Huffman 编码

```
              +--------------+
              |   f1.txt     |
              +------+-------+
                     |
                     v
              +------+-------+
              |   Stat()     |
              | 字符频度统计 |
              +------+-------+
                     |
                     v
              +------+-------+
              | HuffmanBuild |
              | 构建Huffman树|
              +------+-------+
                     |
                     v
              +------+-------+
              | HuffmanCode  |
              | 生成编码表   |
              +------+-------+
                     |
                     v
              +--------------+
              | f1_code.txt  |
              +--------------+
```

---

# 5. 函数调用关系图（Call Graph）

```
main()
 ├── char_code()
 │    ├── Stat()
 │    ├── HuffmanBuild()
 │    │       └── MinHeap::insert/removeFirst
 │    └── HuffmanCode()
 │
 ├── File_Code()      # TODO
 └── File_Decode()    # TODO
```

---

# 6. 输出文件说明（Output Files）

## 6.1 `f1_code.txt`
基础要求输出：
```
Character  Frequency  Code
 32  58  00        # 空格
, 4  0100
a 21 1001
b 13 101
...
```

- 第一列：字符（ASCII）
- 第二列：频度
- 第三列：Huffman 编码

---

# 7. 后续功能扩展（TODO 计划）

## 7.1 中级要求：按 bit 编码整个文本（File_Code）

需要实现：

- `Write(bit)`：将 0/1 写入字节缓冲区  
- 输出到 `f1_result.huf`

---

## 7.2 高级要求：解码（File_Decode）

核心思路：
```
从二进制文件读取 -> 从根开始遍历 Huffman 树
0 → 左
1 → 右
到叶子结点 → 输出字符
```

输出到 `f1_reconstruct.txt`

---



