import math
import pickle


# 定义Grid类，二维方阵容器
class Grid:
    def __init__(self, box_size):
        """构造函数，输入是宫格的大小，比如BOX_SIZE为3"""
        self.BOX_SIZE = box_size
        self.GRID_SIZE = box_size * box_size
        self.grid = [""] * self.GRID_SIZE
        
    def __del__(self):
        """析构函数，释放内存"""
        del self.grid
        print("Grid object is deleted")
        pass    
    
    def _check(self):
        """检查宫格是否有效"""
        if self.grid.size == 0 or self.grid.size() != self.GRID_SIZE or self.BOX_SIZE * self.BOX_SIZE != self.GRID_SIZE:
            return False
        return True

    def get_row(self, row):
        """返回第row行"""
        return self.grid[row]

    def get_column(self, col):
        """返回第col列"""
        return ''.join(self.grid[row][col] for row in range(self.GRID_SIZE))

    def get_box(self, row, col):
        """返回(row, col)位置所在box的所有元素"""
        start_row = (row // self.BOX_SIZE) * self.BOX_SIZE
        start_col = (col // self.BOX_SIZE) * self.BOX_SIZE
        box = ""
        for r in range(start_row, start_row + self.BOX_SIZE):
            for c in range(start_col, start_col + self.BOX_SIZE):
                box += self.grid[r][c]
        return box

    def rows(self):
        """返回按行排的grid"""
        return self.grid

    def columns(self):
        """返回按列排的grid"""
        return [''.join(self.grid[row][col] for row in range(self.GRID_SIZE)) for col in range(self.GRID_SIZE)]

    def boxes(self):
        """返回按box排的grid"""
        box_grid = []
        for row in range(0, self.GRID_SIZE, self.BOX_SIZE):
            for col in range(0, self.GRID_SIZE, self.BOX_SIZE):
                box_grid.append(self.get_box(row, col))
        return box_grid
    
    def __eq__(self, other):
        """比较两个Grid是否相等"""
        return isinstance(other, Grid) and self.grid == other.grid


# 定义Sudoku类，继承自Grid类
class Sudoku(Grid):
    def __init__(self, box_size):
        """"构造函数，输入是宫格的大小，比如BOX_SIZE为3"""
        super().__init__(box_size)

    def parse(self, puzzle_str):
        """将输入的字符串转化为Grid"""
        for i in range(self.GRID_SIZE):
            self.grid[i] = puzzle_str[i * self.GRID_SIZE: (i + 1) * self.GRID_SIZE]
        return self.grid

    def get_same_box(self, row, col):
        """返回(row, col)所在box的所有元素"""
        return self.get_box(row, col)

    def get_candidates(self, row, col):
        """返回(row, col)位置的候选值"""
        if self.grid[row][col] != '0':
            return set()  # 如果不是空格，返回空集

        candidates = set('123456789')
        row_values = set(self.get_row(row))
        col_values = set(self.get_column(col))
        box_values = set(self.get_box(row, col))

        used_values = row_values | col_values | box_values
        return candidates - used_values

    def get_inference(self):
        """返回每个单元格的候选值"""
        inferences = []
        for row in range(self.GRID_SIZE):
            row_inferences = []
            for col in range(self.GRID_SIZE):
                if self.grid[row][col] == '0':
                    row_inferences.append(self.get_candidates(row, col))
                else:
                    row_inferences.append({self.grid[row][col]})  # 固定值作为候选
            inferences.append(row_inferences)
        return inferences
    
    def serialize(self, file_path):
        """串行化"""
        with open(file_path, 'wb') as file:
            pickle.dump(self, file)

    # staticmethod
    def deserialize(file_path):
        """外表化"""
        with open(file_path, 'rb') as file:
            return pickle.load(file)

    def __eq__(self, other):
        """比较两个Sudoku是否相等"""
        return isinstance(other, Sudoku) and self.grid == other.grid


def print_grid(grid):
    """打印数独棋盘"""
    for row in grid:
        for ch in row:
            print("| "+ch, end=' ')
        print("|")


def print_inferences(inferences):
    """打印候选值"""
    for row in range(len(inferences)):
        for col in range(len(inferences[row])):
            print(f"({row+1},{col+1}):", end=' ')
            for ch in inferences[row][col]:
                print(ch, end=' ')
            print(end='\t')
        print()

