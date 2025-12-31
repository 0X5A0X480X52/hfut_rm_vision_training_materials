import cv2
import numpy as np
import os
import json

# 用于生成 tag25h9 家族的 JSON 文件

def imread_unicode(path):
    """支持中文路径的 OpenCV 读取"""
    with open(path, 'rb') as f:
        data = f.read()
    arr = np.frombuffer(data, np.uint8)
    img = cv2.imdecode(arr, cv2.IMREAD_GRAYSCALE)
    return img

def extract_tag_matrix(image_path, tag_size=5):
    img = imread_unicode(image_path)
    if img is None:
        raise ValueError(f"无法读取图片 {image_path}")

    img = img[:img.shape[1], :]  # 裁剪掉底部多余区域
    _, bw = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
    
    # cv2.imshow("BW", bw)
    # cv2.waitKey(0)
    
    print("Image shape:", bw.shape)

    h, w = bw.shape
    cell_h = h // 11
    cell_w = w // 11

    tag_matrix = np.zeros((tag_size, tag_size), dtype=int)

    for i in range(tag_size):
        for j in range(tag_size):
            # ✅ 修正中心格子索引
            y = (i + 3) * cell_h + cell_h // 2
            x = (j + 3) * cell_w + cell_w // 2

            # ⚠️ 把最后一行 (i=4) 修正到第8格
            if i == tag_size - 1:
                y = (i + 3) * cell_h + cell_h // 2
            if j == tag_size - 1:
                x = (j + 3) * cell_w + cell_w // 2

            tag_matrix[i, j] = 1 if bw[y, x] > 127 else 0

    return tag_matrix.tolist()

def save_tag_family_json(folder_path, family_name="tag25h9"):
    result = {}
    for file in os.listdir(folder_path):
        if file.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp')):
            tag_id = os.path.splitext(file)[0]  # 假设文件名为 ID
            file_path = os.path.join(folder_path, file)
            try:
                matrix = extract_tag_matrix(file_path)
                # 如果不显示窗口，则无需销毁
                # ...existing code...
                key = f"{tag_id}"
                result[key] = matrix
            except Exception as e:
                print(f"处理 {file} 出错: {e}")

    # 保存为 JSON
    json_path = os.path.join(folder_path, f"{family_name}.json")
    with open(json_path, 'w', encoding='utf-8') as f:
        json.dump(result, f, indent=2, ensure_ascii=False)
    print(f"已保存 JSON 文件: {json_path}")

# 示例用法
folder = r".\AprilTag"  # 注意 r 前缀
save_tag_family_json(folder)
