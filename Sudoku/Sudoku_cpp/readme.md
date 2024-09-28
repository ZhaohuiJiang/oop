## C++实现Sudoku类



### 对象创建

两个类，一个是宫格类，是一个二维方阵容器，另一个是数独类，继承自Grid。

```c++
// 宫格类，二维方阵容器
class Grid {
protected:
    vector<string> grid;
    int BOX_SIZE; // 宫格的大小，比如9x9的数独就是3x3的box
    int GRID_SIZE; // 整个方阵的大小，比如9x9的数独GRID_SIZE就是9

public:
    // 构造函数，输入是宫格的大小，比如BOX_SIZE为3
    Grid(int boxSize) : BOX_SIZE(boxSize), GRID_SIZE(boxSize * boxSize);

    // 构造函数，输入是棋盘的字符串数组
    Grid(vector<string> &Grid);

    // 拷贝构造函数
    Grid(Grid &others);

    // 析构函数
    ~Grid();

    // 检查宫格是否有效
    void _check();

    // 获取某一行
    string getRow(int row);

    // 获取某一列
    string getColumn(int col);

    // 获取某个box，输入是grid中的行和列
    string getBox(int row, int col);

    // 返回按行排的grid
    vector<string> rows();

    // 返回按列排的grid
    vector<string> columns();

    // 返回按box排的grid
    vector<string> boxes();
	
    // 比较：比较两个Grid对象是否相同
    bool operator==(const Grid& other)；
};


// 数独类，继承自Grid
class Sudoku : public Grid {
public:
    // 使用Grid的构造函数
    Sudoku(int boxSize) : Grid(boxSize) {}

    // 解析输入的字符串，将其转化为Grid
    vector<string> parse(const string &str);

    // 获取指定位置(row, col)所在的box的所有元素
    string getSameBox(int row, int col);

    // 获取指定位置(row, col)的候选值
    set<char> getCandidates(int row, int col);

    // 获取每个单元格的候选值（推理结果）
    vector<vector<set<char>>> getInference();
    
    // 串行化: 将Grid转化为字符串
    string serialize()；

    // 外表化: 静态方法，从字符串中创建 Sudoku 对象。
    static Sudoku deserialize(const string &str, int boxSize)；

    // Sudoku类的比较
    bool operator==(const Sudoku& other)；
};
```



### 初始化

构造函数。

```c++
// 构造函数，输入是宫格的大小，比如BOX_SIZE为3
Grid(int boxSize) : BOX_SIZE(boxSize), GRID_SIZE(boxSize * boxSize) {
    grid.resize(GRID_SIZE);
}

// 构造函数，输入是棋盘的字符串数组
Grid(vector<string> &Grid)  {
    grid = Grid;
    BOX_SIZE = sqrt(Grid.size());
    GRID_SIZE = Grid.size();
}
```



### 克隆

拷贝构造函数。

```cpp
// 拷贝构造函数
Grid(Grid &others)  {
    grid = others.grid;
    BOX_SIZE = others.BOX_SIZE;
    GRID_SIZE = others.GRID_SIZE;
}
```



### 串行化

将Grid转化为字符串

```cpp
// 串行化: 将Grid转化为字符串
string serialize() const {
    string result;
    for (const auto &row : grid) {
        result += row;
    }
    return result;
}
```



### 外表化

静态方法，从字符串中创建 Sudoku 对象。

```cpp
// 外表化: 静态方法，从字符串中创建 Sudoku 对象。
static Sudoku deserialize(const string &str, int boxSize) {
    Sudoku sudoku(boxSize);
    sudoku.parse(str);
    return sudoku;
}
```



### 比较

比较两个Grid对象是否相同，

```cpp
// 比较：比较两个Grid对象是否相同
bool operator==(const Grid& other) const {
    return grid == other.grid;
}


// Sudoku类的比较
bool operator==(const Sudoku& other) const {
    return Grid::operator==(other);
}
```



### 测试

测试用例：

```cpp
string puzzle = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";

Sudoku sudoku(3); // 创建一个宫格大小为3x3的数独实例
sudoku.parse(puzzle); // 解析输入字符串

// 输出解析后的棋盘
print_grid(sudoku);

// 输出推理的候选值
print_inferences(sudoku);
```

测试结果：

```
Parsed Sudoku Grid:
| 0 | 1 | 7 | 9 | 0 | 3 | 6 | 0 | 0 |
| 0 | 0 | 0 | 0 | 8 | 0 | 0 | 0 | 0 |
| 9 | 0 | 0 | 0 | 0 | 0 | 5 | 0 | 7 |
| 0 | 7 | 2 | 0 | 1 | 0 | 4 | 3 | 0 |
| 0 | 0 | 0 | 4 | 0 | 2 | 0 | 7 | 0 |
| 0 | 6 | 4 | 3 | 7 | 0 | 2 | 5 | 0 |
| 7 | 0 | 1 | 0 | 0 | 0 | 0 | 6 | 5 |
| 0 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 |
| 0 | 0 | 5 | 6 | 0 | 1 | 7 | 2 | 0 |

Candidates:
(1,1): 2 4 5 8  (1,2): 1        (1,3): 7        (1,4): 9        (1,5): 2 4 5    (1,6): 3        (1,7): 6        (1,8): 4 8  (1,9): 2 4 8
(2,1): 2 3 4 5 6        (2,2): 2 3 4 5  (2,3): 3 6      (2,4): 1 2 5 7  (2,5): 8        (2,6): 4 5 6 7  (2,7): 1 3 9        (2,8): 1 4 9    (2,9): 1 2 3 4 9
(3,1): 9        (3,2): 2 3 4 8  (3,3): 3 6 8    (3,4): 1 2      (3,5): 2 4 6    (3,6): 4 6      (3,7): 5        (3,8): 1 4 8        (3,9): 7
(4,1): 5 8      (4,2): 7        (4,3): 2        (4,4): 5 8      (4,5): 1        (4,6): 5 6 8 9  (4,7): 4        (4,8): 3    (4,9): 6 8 9
(5,1): 1 3 5 8  (5,2): 3 5 8 9  (5,3): 3 8 9    (5,4): 4        (5,5): 5 6 9    (5,6): 2        (5,7): 1 8 9    (5,8): 7    (5,9): 1 6 8 9
(6,1): 1 8      (6,2): 6        (6,3): 4        (6,4): 3        (6,5): 7        (6,6): 8 9      (6,7): 2        (6,8): 5    (6,9): 1 8 9
(7,1): 7        (7,2): 2 3 4 8 9        (7,3): 1        (7,4): 2 8      (7,5): 2 4 9    (7,6): 4 8 9    (7,7): 3 8 9        (7,8): 6        (7,9): 5
(8,1): 2 4 6 8  (8,2): 2 4 8 9  (8,3): 6 8 9    (8,4): 2 5 7 8  (8,5): 3        (8,6): 4 5 7 8 9        (8,7): 1 8 9        (8,8): 1 4 8 9  (8,9): 1 4 8 9
(9,1): 3 4 8    (9,2): 3 4 8 9  (9,3): 5        (9,4): 6        (9,5): 4 9      (9,6): 1        (9,7): 7        (9,8): 2    (9,9): 3 4 8 9
```

