#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

// 宫格类，二维方阵容器
class Grid {
protected:
    vector<string> grid;
    int BOX_SIZE; // 宫格的大小，比如9x9的数独就是3x3的box
    int GRID_SIZE; // 整个方阵的大小，比如9x9的数独GRID_SIZE就是9

public:
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

    // 拷贝构造函数
    Grid(Grid &others)  {
        grid = others.grid;
        BOX_SIZE = others.BOX_SIZE;
        GRID_SIZE = others.GRID_SIZE;
    }

    // 析构函数
    ~Grid() {
        grid.clear();
    }

    // 检查宫格是否有效
    void _check() {
        if(!grid.size() || grid.size() != GRID_SIZE || BOX_SIZE * BOX_SIZE != GRID_SIZE) {
            throw "Invalid container grid!";
        }
    }

    // 获取某一行
    string getRow(int row) const {
        return grid[row];
    }

    // 获取某一列
    string getColumn(int col) const {
        string column;
        for (int row = 0; row < GRID_SIZE; ++row) {
            column += grid[row][col];
        }
        return column;
    }

    // 获取某个box，输入是grid中的行和列
    string getBox(int row, int col) const {
        int startRow = (row / BOX_SIZE) * BOX_SIZE;
        int startCol = (col / BOX_SIZE) * BOX_SIZE;
        string box;
        for (int r = startRow; r < startRow + BOX_SIZE; ++r) {
            for (int c = startCol; c < startCol + BOX_SIZE; ++c) {
                box += grid[r][c];
            }
        }
        return box;
    }

    // 返回按行排的grid
    vector<string> rows() const {
        return grid;
    }

    // 返回按列排的grid
    vector<string> columns() const {
        vector<string> cols(GRID_SIZE);
        for (int col = 0; col < GRID_SIZE; ++col) {
            cols[col] = getColumn(col);
        }
        return cols;
    }

    // 返回按box排的grid
    vector<string> boxes() const {
        vector<string> boxGrid(GRID_SIZE);
        int index = 0;
        for (int row = 0; row < GRID_SIZE; row += BOX_SIZE) {
            for (int col = 0; col < GRID_SIZE; col += BOX_SIZE) {
                boxGrid[index++] = getBox(row, col);
            }
        }
        return boxGrid;
    }

    // 比较：比较两个Grid对象是否相同
    bool operator==(const Grid& other) const {
        return grid == other.grid;
    }

};


// 数独类，继承自Grid
class Sudoku : public Grid {
public:
    // 使用Grid的构造函数
    Sudoku(int boxSize) : Grid(boxSize) {}

    // 解析输入的字符串，将其转化为Grid
    vector<string> parse(const string &str) {
        for (int i = 0; i < GRID_SIZE; ++i) {
            grid[i] = str.substr(i * GRID_SIZE, GRID_SIZE);
        }
        return grid;
    }

    // 获取指定位置(row, col)所在的box的所有元素
    string getSameBox(int row, int col) {
        return getBox(row, col);
    }

    // 获取指定位置(row, col)的候选值
    set<char> getCandidates(int row, int col) {
        if (grid[row][col] != '0') return {}; // 非空格返回空集

        set<char> candidates = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        string rowValues = getRow(row);
        string colValues = getColumn(col);
        string boxValues = getBox(row, col);

        // 移除已经存在的值
        for (char ch : rowValues) candidates.erase(ch);
        for (char ch : colValues) candidates.erase(ch);
        for (char ch : boxValues) candidates.erase(ch);

        return candidates;
    }

    // 获取每个单元格的候选值（推理结果）
    vector<vector<set<char>>> getInference() {
        vector<vector<set<char>>> inferences(GRID_SIZE, vector<set<char>>(GRID_SIZE));

        // 遍历每个格子，获取候选值
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                if (grid[row][col] == '0') {
                    inferences[row][col] = getCandidates(row, col);
                } else {
                    inferences[row][col] = {grid[row][col]}; // 固定的值
                }
            }
        }

        return inferences;
    }

    // 串行化: 将Grid转化为字符串
    string serialize() const {
        string result;
        for (const auto &row : grid) {
            result += row;
        }
        return result;
    }

    // 外表化: 静态方法，从字符串中创建 Sudoku 对象。
    static Sudoku deserialize(const string &str, int boxSize) {
        Sudoku sudoku(boxSize);
        sudoku.parse(str);
        return sudoku;
    }

    // Sudoku类的比较
    bool operator==(const Sudoku& other) const {
        return Grid::operator==(other);
    }
};


// 打印数独棋盘
void print_grid(Sudoku &sudoku) {
    // 输出解析后的棋盘
    cout << "Parsed Sudoku Grid:" << endl;
    for (const auto& row : sudoku.rows()) {
        for (const auto& ch : row) {
            cout << "| " << ch << " ";
        }
        cout << "|" << endl;
    }
}


// 打印推理的候选值
void print_inferences(Sudoku &sudoku) {
    // 输出推理的候选值
    auto inferences = sudoku.getInference();
    cout << "\nCandidates:" << endl;

    
    for (int row = 0; row < sudoku.rows().size(); row++) {
        for (int col = 0; col < sudoku.rows().size(); col++) {
            cout << "(" << row+1 << "," << col+1 << "): ";
            for (char candidate : inferences[row][col]) {
                cout << candidate << " ";
            }
            cout << "\t";
        }
        cout << endl;
    }
}

