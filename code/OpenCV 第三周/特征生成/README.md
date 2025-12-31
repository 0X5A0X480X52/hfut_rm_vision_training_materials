# 测控项目DEMO

## 项目简介

本项目旨在实现测控相关功能，包含目标生成、标签生成以及检测功能。通过使用 AprilTag 技术，项目能够高效地处理目标检测和标记。

## 文件结构

```bash
.
├── generateTag25h9Json.py   # 生成 tag25h9 JSON 文件的脚本
├── generateTarget.py        # 目标生成脚本
├── README.md                # 项目说明文件
├── requirements.txt         # 依赖项列表
└── AprilTag/
    └── tag25h9.json         # 预生成的 tag25h9 JSON 文件
```

## 使用说明

### 1. 准备工作

在运行脚本之前，请确保已安装所需的 Python 库。可以使用以下命令安装依赖项：

```bash
pip install -r requirements.txt
```

确保 `AprilTag` 文件夹存在，并包含所需的标签图像文件。

### 2. generateTag25h9Json.py

`generateTag25h9Json.py` 用于生成 tag25h9 家族的 JSON 文件

- **运行方式**：

  ```powershell
  python generateTag25h9Json.py
  ```

- **功能描述**：
  - 从指定文件夹中读取标签图像文件（支持 PNG、JPG 等格式）。
  - 提取标签的二值矩阵并保存为 JSON 文件。
  - 输出文件路径：`./AprilTag/tag25h9.json`。

### 3. generateTarget.py

`generateTarget.py` 是一个目标生成脚本，主要功能是生成检测用的特征图像

- **运行方式**：

  ```powershell
  python generateTarget.py
  ```

- **功能描述**：
  - 生成包含四个角标签（ID 0, 1, 2, 3）的特征图。
  - 绘制彩色矩形、黑色边框和中心数字。
  - 输出文件路径：`feature_map.png`。
