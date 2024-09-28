## python实现Sudoku类



### 对象创建

两个类，一个是Grid类，是一个二维方阵容器，另一个是数独类，继承自Grid。

```python
# 定义Grid类，二维方阵容器
class Grid:
    def __init__(self, box_size):
		"""构造函数，输入是宫格的大小，比如BOX_SIZE为3"""
        
    def __del__(self):
		"""析构函数，释放内存"""

    
    def _check(self):
        """检查宫格是否有效"""


    def get_row(self, row):
        """返回第row行"""

    def get_column(self, col):
        """返回第col列"""

    def get_box(self, row, col):
        """返回(row, col)位置所在box的所有元素"""

    def rows(self):
        """返回按行排的grid"""

    def columns(self):
        """返回按列排的grid"""

    def boxes(self):
        """返回按box排的grid"""
    
    def __eq__(self, other):
        """比较两个Grid是否相等"""

# 定义Sudoku类，继承自Grid类
class Sudoku(Grid):
    def __init__(self, box_size):
		""""构造函数，输入是宫格的大小，比如BOX_SIZE为3"""

    def parse(self, puzzle_str):
        """将输入的字符串转化为Grid"""

    def get_same_box(self, row, col):
        """返回(row, col)所在box的所有元素"""

    def get_candidates(self, row, col):
        """返回(row, col)位置的候选值"""

    def get_inference(self):
        """返回每个单元格的候选值"""
    
    def serialize(self, file_path):
        """串行化"""

    # staticmethod
    def deserialize(file_path):
        """外表化"""

    def __eq__(self, other):
        """比较两个Sudoku是否相等"""

```



### 初始化

构造函数。

```python
def __init__(self, box_size):
"""构造函数，输入是宫格的大小，比如BOX_SIZE为3"""
    self.BOX_SIZE = box_size
    self.GRID_SIZE = box_size * box_size
    self.grid = [""] * self.GRID_SIZE
```





### 串行化

使用`pickle` 来实现串行化和外表化

```python
def serialize(self, file_path):
    """串行化"""
    with open(file_path, 'wb') as file:
        pickle.dump(self, file)
```



### 外表化

静态方法

```python
# staticmethod
def deserialize(file_path):
    """外表化"""
    with open(file_path, 'rb') as file:
        return pickle.load(file)
```



### 比较

比较两个Grid对象是否相同，

```python
def __eq__(self, other):
    """比较两个Grid是否相等"""
    return isinstance(other, Grid) and self.grid == other.grid

def __eq__(self, other):
    """比较两个Sudoku是否相等"""
    return isinstance(other, Sudoku) and self.grid == other.grid
```



### 测试

测试用例：

```python
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
(1,1): 8 5 4 2  (1,2): 1        (1,3): 7        (1,4): 9        (1,5): 5 4 2    (1,6): 3        (1,7): 6        (1,8): 8 4  (1,9): 8 4 2
(2,1): 6 4 2 3 5        (2,2): 2 5 4 3  (2,3): 6 3      (2,4): 1 5 2 7  (2,5): 8        (2,6): 6 5 4 7  (2,7): 1 3 9        (2,8): 1 4 9    (2,9): 4 2 3 1 9 
(3,1): 9        (3,2): 2 8 4 3  (3,3): 6 8 3    (3,4): 1 2      (3,5): 6 4 2    (3,6): 6 4      (3,7): 5        (3,8): 1 8 4        (3,9): 7
(4,1): 8 5      (4,2): 7        (4,3): 2        (4,4): 8 5      (4,5): 1        (4,6): 6 8 5 9  (4,7): 4        (4,8): 3    (4,9): 6 8 9
(5,1): 1 8 5 3  (5,2): 8 5 3 9  (5,3): 8 3 9    (5,4): 4        (5,5): 6 5 9    (5,6): 2        (5,7): 1 8 9    (5,8): 7    (5,9): 1 6 8 9
(6,1): 1 8      (6,2): 6        (6,3): 4        (6,4): 3        (6,5): 7        (6,6): 8 9      (6,7): 2        (6,8): 5    (6,9): 1 8 9
(7,1): 7        (7,2): 4 2 3 9 8        (7,3): 1        (7,4): 8 2      (7,5): 4 2 9    (7,6): 8 4 9    (7,7): 8 3 9        (7,8): 6        (7,9): 5
(8,1): 6 8 4 2  (8,2): 8 4 2 9  (8,3): 6 8 9    (8,4): 8 5 2 7  (8,5): 3        (8,6): 4 5 9 8 7        (8,7): 1 8 9        (8,8): 1 8 4 9  (8,9): 1 8 4 9
(9,1): 8 4 3    (9,2): 8 4 3 9  (9,3): 5        (9,4): 6        (9,5): 4 9      (9,6): 1        (9,7): 7        (9,8): 2    (9,9): 8 4 3 9
Grid object is deleted
```

