## 实现Sudoku类

按照自己喜好，分别用两种语言，一种静态类型（C++、Java、……），一种动态类型（Python、JavaScript、……），按设计实现Sundoku模块（业务代码、测试代码、文档）。

![goal](images/goal.png)

### 设计

![design](images/design.png)

### 要求

1. 业务功能

2. 1. Input：017903600000080000900000507072010430000402070064370250701000065000030000005601720 
   2. 更多测例，可从 https://www.sudokuwiki.org/ 获取
   3. 解析字符串输入，得到Sudoku实例
   4. 推理棋盘，得到各单元格候选值
   5. 场景下其它合理功能

3. 代码质量

4. 1. OO基础技术：实现的Sudoku类应当符合所用语言OOP的技术惯例，包括必要的基础技术方法，包括并不限于：对象创建、初始化、克隆、串行化、外表化、比较（序）
   2. 正确性：必要的测试代码和测试用例
   3. 可理解性：恰当的命名、合理的模块（函数）划分、必要的注释