from Sudoku import Sudoku, print_grid, print_inferences


def main():
    puzzle = "017903600000080000900000507072010430000402070064370250701000065000030000005601720"
    
    sudoku = Sudoku(3)  # 创建一个宫格大小为3x3的数独实例
    sudoku.parse(puzzle)  # 解析输入字符串

    # 输出解析后的棋盘
    print("Parsed Sudoku Grid:")
    print_grid(sudoku.rows())

    # 输出推理的候选值
    print("\nCandidates:")
    inferences = sudoku.get_inference()
    print_inferences(inferences)

if __name__ == "__main__":
    main()