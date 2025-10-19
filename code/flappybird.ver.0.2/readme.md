# Flappy Bird Ver 2.0 - 控制台版本

## 项目简介

这是一个基于 C++ 实现的控制台版 Flappy Bird 游戏，作为 **Day 21：综合项目② - 控制台 Flappy Bird（扩展挑战）** 的实现。项目采用面向对象的设计思想，实现了经典的 Flappy Bird 游戏玩法，包括分数记录、历史数据保存等功能。

**作者**: Amatrix
**日期**: 2024/05/29  
**版本**: 2.0

---

## 功能特性

- ✨ **核心游戏机制**：小鸟自由下落，玩家通过空格键控制小鸟上升
- 🎮 **随机障碍物生成**：障碍物随机生成开口位置，增加游戏挑战性
- 📊 **分数系统**：实时显示当前分数和游戏距离
- 💾 **数据持久化**：保存游戏记录到本地文件，支持查看历史最高分
- 🏆 **排行榜功能**：显示历史游戏记录和最高分玩家
- 🔄 **游戏循环**：支持连续游戏，无需重启程序

---

## 项目结构

```bash
flappybird.ver.0.2/
├── main.cpp              # 主程序入口，游戏流程控制
├── CMakeLists.txt        # CMake 构建配置文件
├── data.txt              # 游戏数据存储文件
├── README.md             # 项目说明文档
├── head/                 # 头文件目录
│   ├── bird.hpp          # 小鸟类定义
│   ├── barrier.hpp       # 障碍物类定义
│   ├── mainwindow.hpp    # 主窗口类定义
│   └── queue.hpp         # 队列数据结构定义
└── src/                  # 源文件目录
    ├── bird.cpp          # 小鸟类实现
    ├── barrier.cpp       # 障碍物类实现
    ├── mainwindow.cpp    # 主窗口类实现
    └── queue.cpp         # 队列数据结构实现
```

---

## 核心设计思路

### 1. 模块化设计

项目采用面向对象的设计方法，将游戏的各个组成部分抽象为独立的模块：

#### 1.1 Bird（小鸟）模块

**数据结构**：

```cpp
struct bird {
    int x;         // 小鸟在整个游戏中的横坐标
    int screen_x;  // 小鸟在显示区域中的横坐标
    int y;         // 小鸟在整个游戏中的纵坐标
};
```

**核心功能**：

- `bird__init__()`: 初始化小鸟的初始位置
- `bird_responseKeyBoard()`: 响应键盘输入，让小鸟上升
- `bird_move()`: 小鸟的自然下落和前进

**运动机制**：

- 小鸟每帧自动下降 1 个单位（`BIRD_MOVE_DOWN = 1`）
- 按下空格键后上升 2 个单位（`BIRD_MOVE_UP_KEYBOARD = -2`）
- 横坐标持续增加，模拟向前飞行

#### 1.2 Barrier（障碍物）模块

**数据结构**：

```cpp
struct barrier {
    int x;            // 障碍物在整个游戏中的（最左上角）横坐标
    int width;        // 障碍物的总宽度（默认 4）
    int height;       // 障碍物的总高度
    int hole_y;       // 障碍物孔洞的（最左上角）纵坐标
    int hole_height;  // 障碍物孔洞的总高度（默认 3）
};
```

**核心功能**：

- `barrier__init__()`: 初始化障碍物，随机分配开口位置
- `barrier_getRandHole_y()`: 使用随机数生成器确定开口的纵坐标

**设计亮点**：

- 障碍物由上下两部分组成，中间留有开口供小鸟通过
- 开口位置随机生成，确保每次游戏体验不同
- 固定宽度（4 个字符）和开口高度（3 个字符），平衡游戏难度

#### 1.3 Queue（队列）模块

**数据结构**：

```cpp
struct QueueRecord {
    int capacity;      // 队列的容量
    int front;         // 队列首元素索引
    int rear;          // 队列尾元素索引
    int size;          // 队列内已存有元素的个数
    ElementType *array; // 队列中用于存放元素的数组（void* 类型）
};
```

**核心功能**：

- `queue_createQueue()`: 创建队列
- `queue_enqueue()`: 元素入队
- `queue_dequeue()`: 元素出队
- `queue_isEmpty()` / `queue_isFull()`: 队列状态检查

**应用场景**：

1. **障碍物队列**（`barrierQueue`）：管理当前屏幕上的所有障碍物
2. **画布缓冲队列**（`canvasCache`）：缓存待显示的画布列数据

**设计优势**：

- 使用循环数组实现，避免频繁的内存分配
- 泛型设计（`void*`），可以存储任意类型的指针

#### 1.4 MainWindow（主窗口）模块

**数据结构**：

```cpp
struct mainwindow {
    int waitTime;              // 窗口的刷新间隔（默认 200ms）
    int height;                // 窗口的高度（默认 15）
    int width;                 // 窗口的宽度（默认 80）
    int x;                     // 窗口（最左上角的）坐标
    int score;                 // 游戏的分数
    
    struct bird * bird;        // 窗口的 bird
    
    int barrierHoleHeight;     // 障碍物开口高度
    int barrierQueueMaxNum;    // 障碍物队列最大容量（默认 5）
    int barrierAddWaitTime;    // 新障碍物生成间隔（默认 20 帧）
    int cnt_barrierAddWaitTime; // 障碍物生成计时器
    Queue barrierQueue;        // 障碍物队列
    
    Queue canvasCache;         // 画布缓冲队列
    char canvas[HEIGHT][WIDTH]; // 画布（循环数组）
    int frontColOfCanvas;      // 画布循环数组的首列索引
};
```

**核心功能**：

1. **初始化与资源管理**
   - `mainwindow__init__()`: 初始化游戏窗口、小鸟、队列等
   - `mainwindow__free__()`: 释放所有动态分配的内存

2. **游戏逻辑更新**
   - `mainwindow_update()`: 与用户输入无关的更新（小鸟移动、障碍物更新）
   - `mainwindow_responseKeyBoard()`: 响应键盘输入
   - `mainwindow_updateBarrierQueue()`: 管理障碍物的生成和销毁

3. **碰撞检测**
   - `mainwindow_checkIsBirdHit()`: 检测小鸟是否碰撞
   - `mainwindow_isBirdHitBarrier()`: 检测小鸟与障碍物的碰撞
   - `mainwindow_isBirdHitMargin()`: 检测小鸟与窗口边界的碰撞

4. **渲染系统**
   - `mainwindow_drawBackground()`: 更新画布背景
   - `mainwindow_show()`: 在控制台输出画面

---

### 2. 游戏循环机制

游戏的主循环位于 `mainLoop()` 函数中：

```cpp
int mainLoop() {
    // 1. 初始化游戏窗口
    struct mainwindow *window = ...;
    mainwindow__init__(window);
    
    // 2. 游戏主循环
    while(1) {
        mainwindow_responseKeyBoard(window);  // 响应键盘输入
        mainwindow_update(window);            // 更新游戏状态
        mainwindow_drawBackground(window);    // 更新画布
        mainwindow_show(window);              // 渲染画面
        
        if (mainwindow_checkIsBirdHit(window))  // 碰撞检测
            break;
            
        Sleep(window->waitTime);              // 帧延迟（200ms）
    }
    
    // 3. 显示最终分数并清理资源
    mainwindow_showFinalScore(window);
    score = window->score;
    mainwindow__free__(window);
    return score;
}
```

**循环流程**：

1. **输入处理**：检测是否按下空格键
2. **状态更新**：小鸟移动、障碍物移动、分数更新
3. **画面渲染**：更新画布并输出到控制台
4. **碰撞检测**：判断游戏是否结束
5. **帧延迟**：控制游戏速度（每秒约 5 帧）

---

### 3. 渲染系统设计

#### 3.1 画布循环数组

**设计思路**：

- 使用二维数组 `canvas[HEIGHT][WIDTH]` 表示游戏画面
- 画布是一个**循环列表**，通过 `frontColOfCanvas` 标记首列
- 每帧向左滚动一列，新的一列从右侧加入

**滚动实现**：

```txt
初始状态：frontColOfCanvas = 0
[0][1][2][3][4]...
 ↑

滚动后：frontColOfCanvas = 1
[0][1][2][3][4]...
    ↑
```

#### 3.2 画布缓冲队列

**问题**：障碍物可能比一列宽（宽度为 4），需要提前准备多列数据

**解决方案**：

- 使用 `canvasCache` 队列缓存待显示的列数据
- 每列数据用一个整数表示：
  - `-1`：空列（没有障碍物）
  - `≥0`：障碍物列，值表示开口的起始纵坐标

**渲染流程**：

1. 从 `canvasCache` 中取出一列数据
2. 根据数据更新 `canvas` 的最后一列
3. `frontColOfCanvas` 前移，实现画布滚动
4. 输出整个画布到控制台

#### 3.3 显示优化

**技术手段**：

- `HideCursor()`：隐藏控制台光标，避免闪烁
- `gotoxy(0, 0)`：将光标移到屏幕左上角，避免闪屏
- 直接覆盖输出，而不是清屏后重绘

---

### 4. 障碍物管理系统

#### 4.1 障碍物生成机制

**生成策略**：

- 使用计时器 `cnt_barrierAddWaitTime` 控制生成频率
- 每隔 20 帧（约 4 秒）生成一个新障碍物
- 障碍物队列最多存储 5 个障碍物

**生成流程**：

```cpp
if (cnt_barrierAddWaitTime-- <= 0) {
    cnt_barrierAddWaitTime = barrierAddWaitTime;  // 重置计时器
    mainwindow_newBarrier(window);                 // 生成新障碍物
}
```

**新障碍物创建**（`mainwindow_newBarrier()`）：

1. 创建障碍物结构体，随机生成开口位置
2. 将障碍物加入 `barrierQueue`
3. 向 `canvasCache` 压入障碍物的 4 列数据

#### 4.2 障碍物销毁机制

**销毁时机**：

- 当障碍物完全移出屏幕左侧时（即障碍物的右边缘 < 小鸟的横坐标）
- 此时玩家成功通过障碍物，分数 +1

**销毁流程**：

```cpp
if (!queue_isEmpty(barrierQueue)) {
    struct barrier *barrier = queue_fornt(barrierQueue);
    if ((barrier->x + barrier->width - 1) <= bird->x) {
        mainwindow_deletBarrier(window);  // 释放障碍物
        window->score++;                   // 分数加一
    }
}
```

---

### 5. 碰撞检测系统

#### 5.1 小鸟与障碍物碰撞

**检测逻辑**：

```cpp
int mainwindow_isBirdHitBarrier(struct bird *bird, struct barrier *barrier) {
    // 1. 检查横向位置：小鸟是否在障碍物的横向范围内
    if (bird->x < barrier->x || bird->x > barrier->x + barrier->width - 1)
        return 0;  // 不在障碍物范围内
    
    // 2. 检查纵向位置：小鸟是否在开口范围内
    int minHeight = barrier->hole_y;
    int maxHeight = barrier->hole_y + barrier->hole_height - 1;
    if (bird->y >= minHeight && bird->y <= maxHeight)
        return 0;  // 在开口范围内，安全
    else
        return 1;  // 碰到障碍物
}
```

**碰撞判定原理**：

- 横向判断：小鸟的 x 坐标是否在障碍物的 x 范围内
- 纵向判断：小鸟的 y 坐标是否在开口范围外

#### 5.2 小鸟与边界碰撞

**检测逻辑**：

```cpp
int mainwindow_isBirdHitMargin(struct bird *bird, struct mainwindow *window) {
    if (bird->y >= 0 && bird->y <= window->height - 1)
        return 0;  // 在窗口范围内
    else
        return 1;  // 碰到上下边界
}
```

---

### 6. 数据持久化系统

#### 6.1 数据存储格式

游戏记录保存在 `data.txt` 文件中，每行一条记录：

```txt
SCORE 15 USERNAME Player1 DATE 2024/5/29 14:30:25
SCORE 22 USERNAME Player2 DATE 2024/5/29 15:45:10
```

**记录内容**：

- 分数（SCORE）
- 玩家名称（USERNAME）
- 游戏时间（DATE）

#### 6.2 数据读取（`readData()`）

**功能**：

- 读取历史最高分和对应玩家信息
- 遍历文件所有记录，找出最高分

**实现**：

```cpp
void readData(int *maxScore, char userName[], ...) {
    FILE *fp = fopen(FILENAME, "rw+");
    do {
        fscanf(fp, "SCORE %d USERNAME %s DATE ...", &temReadScore, userName, ...);
        *maxScore = (*maxScore < temReadScore) ? temReadScore : *maxScore;
    } while (flag_endFile != EOF);
    fclose(fp);
}
```

#### 6.3 数据写入（`writeData()`）

**功能**：

- 保存当前游戏记录到文件
- 使用追加模式（"a"），不覆盖历史数据

**实现**：

```cpp
void writeData(int score, char userName[]) {
    time_t now;
    time(&now);
    localtime_s(&t, &now);  // 获取当前时间
    
    FILE *fp = fopen(FILENAME, "a");
    fprintf(fp, "SCORE %d USERNAME %s DATE %d/%d/%d %d:%d:%d\n", ...);
    fclose(fp);
}
```

#### 6.4 历史记录查看（`printData()`）

**功能**：

- 显示所有历史游戏记录
- 按顺序输出分数、玩家名和游戏时间

---

### 7. 用户交互设计

#### 7.1 游戏流程

```txt
[1] 启动游戏
    ↓
[2] 输入玩家名称
    ↓
[3] 查看游戏说明
    ↓
[4] 开始游戏
    ↓
[5] 游戏结束，显示分数
    ↓
[6] 选择：再来一局 / 查看历史记录 / 退出
    ↓
    回到 [4] 或退出
```

#### 7.2 菜单系统

**主菜单**：

```txt
【是否再来一局？】
 输入 1 重新开始
 输入 2 查看历史记录
 其他输入退出
```

**功能实现**：

```cpp
switch (flag) {
case 1:
    // 重新开始游戏
    break;
case 2:
    // 显示历史记录
    printData();
    break;
default:
    // 退出游戏
    flag = -1;
    break;
}
```

---

## 技术要点

### 1. Windows API 应用

- **控制台编码设置**：`SetConsoleOutputCP(65001)` - 支持 UTF-8 中文显示
- **光标控制**：`SetConsoleCursorInfo()` - 隐藏光标，`SetConsoleCursorPosition()` - 移动光标
- **键盘输入检测**：`kbhit()` 和 `getch()` - 非阻塞式键盘输入

### 2. 时间管理

- **游戏延迟**：`Sleep(waitTime)` - 控制游戏帧率（约 5 FPS）
- **时间戳**：`time()` 和 `localtime_s()` - 记录游戏时间

### 3. 随机数生成

- 使用 `srand(time(&t))` 初始化随机种子
- 使用 `rand() % range` 生成障碍物开口位置

### 4. 文件操作

- 文本文件的读写操作（`fopen`, `fprintf`, `fscanf`）
- 追加模式保存历史记录

### 5. 内存管理

- 动态内存分配（`malloc`）和释放（`free`）
- 队列中存储 `void*` 指针，需要正确的类型转换

---

## 构建与运行

### 使用 CMake 构建

Linux / macOS 用户可使用以下命令：

```bash
# 创建构建目录
mkdir build
cd build

# 生成构建文件
cmake ..

# 编译项目
cmake --build .

# 运行游戏
./flappybird.ver.0.2
```

Windows 用户可使用以下命令：

```powershell
# 创建构建目录
mkdir build
cd build

# 生成构建文件
cmake -G "MinGW Makefiles" ..

# 编译项目
mingw32-make

# 运行游戏
.\flappybird.ver.0.2.exe
```

### 使用 Visual Studio

1. 打开 `CMakeLists.txt`
2. Visual Studio 会自动配置 CMake 项目
3. 按 F5 运行

---

## 游戏说明

### 操作方法

- **空格键**：让小鸟向上飞（上升 2 个单位）
- 小鸟会自动下落（每帧下降 1 个单位）

### 游戏规则

1. 避免碰到上下边界
2. 避免碰到障碍物（只能从开口通过）
3. 每成功通过一个障碍物，分数 +1
4. 游戏结束后可以查看历史最高分

### 游戏参数

| 参数 | 默认值 | 说明 |
|------|--------|------|
| 窗口宽度 | 80 | 游戏区域宽度 |
| 窗口高度 | 15 | 游戏区域高度 |
| 刷新间隔 | 200ms | 游戏帧率约 5 FPS |
| 障碍物宽度 | 4 | 障碍物的字符宽度 |
| 障碍物开口高度 | 3-4 | 可通过的开口大小 |
| 障碍物生成间隔 | 20 帧 | 约 4 秒生成一个 |
| 小鸟下降速度 | 1 | 每帧下降距离 |
| 小鸟上升速度 | 2 | 按空格后上升距离 |

---

## 设计亮点

1. **模块化设计**：清晰的模块划分，易于理解和维护
2. **循环数组优化**：画布和队列使用循环数组，提高内存利用率
3. **缓冲队列机制**：预先缓存画布数据，实现平滑滚动
4. **数据持久化**：游戏记录永久保存，支持查看历史最高分
5. **非阻塞输入**：使用 `kbhit()` 实现流畅的游戏体验
6. **无闪烁渲染**：通过光标控制和覆盖输出，避免画面闪烁

---

## 可能的改进方向

1. **难度系统**：根据分数增加游戏速度或减小开口大小
2. **音效支持**：添加背景音乐和音效（需要额外库）
3. **颜色显示**：使用 Windows API 设置文字颜色，美化界面
4. **多人模式**：记录多个玩家的成绩，实现排行榜
5. **暂停功能**：允许玩家暂停和恢复游戏
6. **配置文件**：允许玩家自定义游戏参数
7. **跨平台支持**：使用 ncurses 等库实现 Linux 支持

---

## 开发环境

- **语言**：C++
- **编译器**：支持 C++11 及以上
- **平台**：Windows（使用了 Windows API）
- **构建工具**：CMake 3.5+
- **IDE**：Visual Studio / CLion / VS Code

---

## 许可证

本项目为教学项目，仅供学习交流使用。
