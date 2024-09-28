#include "Sudoku.cpp"
using namespace std;

int main() {
    string puzzle = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";

    Sudoku sudoku(3); // 创建一个宫格大小为3x3的数独实例
    sudoku.parse(puzzle); // 解析输入字符串

    // 输出解析后的棋盘
    print_grid(sudoku);

    // 输出推理的候选值
    print_inferences(sudoku);

    return 0;
}
