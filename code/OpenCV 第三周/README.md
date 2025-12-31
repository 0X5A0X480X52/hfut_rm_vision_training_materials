# OpenCV 培训（第三周）资料

本目录包含 OpenCV 三周入门手册的第三周培训资料，主要涵盖特征生成与检测相关内容。包括以下部分：

```bash
./
├── PNP.py                          # 基于特征匹配的位姿估计示例脚本   
├── README.md                       # 本说明文件
├── 双目视觉.py                      # 双目视觉深度估计示例脚本 
├── 特征匹配.py                      # 特征匹配示例脚本
├── 特征描述子.py                    # 特征描述子示例脚本
├── 角点检测.py                      # 角点检测示例脚本
├── image/                        # 示例图片文件夹
│   ├── camera_left.mp4             # 左目摄像头视频
│   ├── camera_right.mp4            # 右目摄像头视频
│   └── feature_map.png             # 特征图像
└── 特征生成/                      # 特征生成项目文件夹
    ├── generateTag25h9Json.py      # 生成 tag25h9 JSON 文件的脚本
    ├── generateTarget.py           # 目标生成脚本
    ├── README.md                   # 特征生成项目说明文件
    ├── requirements.txt            # 依赖项列表  
    └── AprilTag/                 # AprilTag 标签文件夹
        └── tag25h9.json            # 预生成的 tag25h9 JSON 文件
```

其中，`特征生成/` 文件夹下的内容详见其内的 README.md 文件说明。注意：

- 示例脚本均可独立运行，适合作为学习参考，但需要根据实际环境调整路径等参数。
- 特征生成项目依赖于 AprilTag 标签图像文件，请确保 `AprilTag` 文件夹存在，并包含所需的标签图像文件。
