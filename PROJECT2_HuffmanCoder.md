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
# 3. 功能模块说明（Module Description — Detailed Version）

---

## 3.1 `main.cpp` —— 主控制模块（Main Control Module）

该模块负责程序的整体运行流程控制与用户交互，是整个项目的入口。

### 主要职责
- 显示操作菜单  
- 接受用户输入的指令  
- 根据选项调用对应的功能模块  
- 控制程序循环（支持多次操作直到退出）

### 包含的主要函数

---

### **1. `char_code()`**
- **功能**：完成 Huffman 编码器的基础要求。
- **任务内容**：
  - 调用 `Stat()` 读取并统计输入文本文件 `f1.txt` 中各字符出现次数；
  - 调用 `HuffmanBuild()` 生成 Huffman 树；
  - 调用 `HuffmanCode()` 为每个字符生成编码；
  - 将“字符 — 频度 — 编码”三列输出到 `f1_code.txt`。

---

### **2. `File_Code()`**
- **功能**：中级要求的接口（目前仅预留）  
- **预期行为**：
  - 使用编码表对整个文本按 bit 编码  
  - 将压缩后的比特流写入 `.huf` 二进制文件  
  - 未来还可加入压缩比计算

---

### **3. `File_Decode()`**
- **功能**：高级要求的接口（目前仅预留）  
- **预期行为**：
  - 从 `.huf` 文件读取 bit 流  
  - 根据 Huffman 树重建原文本  
  - 输出内容到 `f1_reconstruct.txt`

---

### **主菜单结构**
```
1：统计并输出字符集+频度集+编码集（基本要求）
2：对整个文件编码并生成二进制文件（中级要求）
3：解码出原文本（高级要求）
4：退出
```

---

## 3.2 `Huffman.h` —— 数据结构定义模块（Data Structures & API Definitions）

该模块定义了实现 Huffman 算法所需的核心数据结构，包括节点、树与最小堆，并声明了算法接口。

---

### **① `HuffNode<T>` —— Huffman 树节点**

#### **结构成员**
- `T val`：节点存储的字符（叶节点使用）  
- `int weight`：权值（字符出现频度）  
- `HuffNode *left, *right`：左右子树指针  

#### **特点**
- 内部节点的 `val` 为特殊标识符（如 `'#'`）  
- 叶节点对应实际字符，是编码的终点  
- `weight` 决定节点在最小堆中的优先级  

---

### **② `HuffTree<T>` —— Huffman 树结构**

#### **主要成员**
- `HuffNode<T> *root`：树根指针  

#### **功能接口**
- `HuffTree(T v, int w)`：创建单个叶子节点树  
- `HuffTree(HuffTree<T>* left, HuffTree<T>* right)`：创建合并树  
- `int weight() const`：返回树根频度，用于堆比较  
- `void print()`：打印树结构（调试用）  

---

### **③ `MinHeap<T>` —— 最小堆（Huffman 树构建的关键）**

构建 Huffman 树需要反复取出当前权值最小的两棵树，因此使用最小堆来优化。

#### **主要方法**
- `void insert(HuffTree<T>* t)`：插入一棵树并保持最小堆性质（上浮）  
- `HuffTree<T>* removeFirst()`：移除权值最小的树（下沉调整）  
- `int size`：当前树数量  

#### **作用**
加速 Huffman 构建过程，使查找最小权树的时间从 O(n) → O(log n)

---

### **公开函数接口**

```cpp
void Stat(char* s, int* w, int& num);
HuffTree<char>* HuffmanBuild(char* s, int* w, int num);
void HuffmanCode(HuffNode<char>* node, char* code, int len, ofstream& fout);
```

说明：

#### **`Stat()`**
- 输入：文本文件  
- 输出：字符集、频度集、字符数量  

#### **`HuffmanBuild()`**
- 输入：字符集和对应权值  
- 输出：构建完成的 Huffman 树  

#### **`HuffmanCode()`**
- 输入：Huffman 树根节点  
- 输出：字符编码表  

---

## 3.3 `Huffman.cpp` —— 算法实现模块（Algorithm Implementation）

该模块完成 Huffman 算法的全部核心逻辑：

1. ASCII 字符频度统计  
2. Huffman 树构建  
3. Huffman 编码生成（递归 DFS）  

---

## **① `Stat()` —— 字符频度统计**

### **功能流程**
1. 初始化 `w[256] = {0}`  
2. 打开 `f1.txt` 并依次读取每个字符  
3. 对应 ASCII 值累加计数：`w[ch]++`  
4. 记录出现过的字符到 `s[]`  
5. 统计非零频度的字符数量 `num`  

### **输出内容**
- `s[]`：字符集  
- `w[]`：频度集  
- `num`：出现的字符个数  

统计结果将用于 Huffman 树构建。

---

## **② `HuffmanBuild()` —— 构建 Huffman 树**

### **核心算法（贪心策略）**

```
重复直到堆中仅剩一棵树：
    1. 从堆中取出权值最小的两棵树 T1, T2
    2. 创建新树：weight = T1.weight + T2.weight
    3. 新树左子树 = T1，右子树 = T2
    4. 将新树插回堆
返回最后剩下的树（即 Huffman 树）
```

### **输入输出**

| 输入 | 输出 |
|------|------|
| 字符集 s[] | HuffmanTree 根节点 |
| 权值集 w[] |  |
| 字符数量 num |  |

整个过程确保每次都选择当前最小的两个权值，形成最优前缀编码。

---

## **③ `HuffmanCode()` —— Huffman 编码生成**

### **编码规则**
- 向左走 → 追加 `'0'`  
- 向右走 → 追加 `'1'`  
- 到达叶子节点 → 输出编码  

### **递归逻辑**

```
function encode(node, code, len):
    if node is leaf:
        输出：val, weight, code
    if node->left:
        code[len+1] = '0'
        encode(node->left, code, len+1)
    if node->right:
        code[len+1] = '1'
        encode(node->right, code, len+1)
```

### **输出示例（f1_code.txt）**

```
Character  Frequency  Code
a 21 010
b 13 0110
c 7 1101
d 4 1110
...
```

### **特点**
- 深度优先遍历构建路径编码  
- 所有编码确保 **前缀码性质**（无编码为另一个编码的前缀）  
- 递归实现简单且易维护  

---

（完）

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



