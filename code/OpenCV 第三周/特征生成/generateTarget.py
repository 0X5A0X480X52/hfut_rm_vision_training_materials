from PIL import Image, ImageDraw, ImageFont
import numpy as np
import os
import json

# 基于 AprilTag tag25h9 家族的特征图生成器，生成检测用的特征图像

# 先加载 JSON 文件
folder = r".\AprilTag" #改为你的 AprilTag 图片文件夹路径
json_path = os.path.join(folder, "tag25h9.json")
with open(json_path, 'r', encoding='utf-8') as f:
    tag_dict = json.load(f)

class FeatureMapGenerator:
    def __init__(self, cell_size=20, grid_size=54, color_map=None):
        self.cell_size = cell_size
        self.grid_size = grid_size
        self.img_size = grid_size * cell_size
        # 默认结构化颜色映射，分为灰度像素值(grayscale)和标记(markers)
        default_colors = {
            'grayscale': {
                0: 'black',
                1: 'black',
                2: 'gray',
                255: 'white'
            },
            'markers': {
                'color1': 'red',
                'color2': 'red',
                'color3': 'red',
                'color4': 'red'
            }
        }
        # 合并用户传入的 color_map（支持按层级覆盖）
        if color_map is None:
            color_map = {}

        # 初始化为默认值的复制，然后按需合并
        self.color_map = {
            'grayscale': default_colors['grayscale'].copy(),
            'markers': default_colors['markers'].copy()
        }
        for k, v in color_map.items():
            if k in self.color_map and isinstance(v, dict):
                self.color_map[k].update(v)
            else:
                self.color_map[k] = v

    def _draw_grid(self, draw):
        """绘制网格线"""
        for i in range(self.grid_size + 1):
            draw.line([(0, i * self.cell_size), (self.img_size, i * self.cell_size)],
                      fill='lightgray', width=1)
            draw.line([(i * self.cell_size, 0), (i * self.cell_size, self.img_size)],
                      fill='lightgray', width=1)

    def _draw_april_tag(self, draw, tag_id, start_x, start_y):
        """绘制一个 AprilTag"""
        april = self._create_april_tag(tag_id)
        for i in range(11):
            for j in range(11):
                pixel_value = int(april[i, j])
                color = self._get_color(pixel_value)
                x1, y1 = (start_x + j) * self.cell_size, (start_y + i) * self.cell_size
                x2, y2 = x1 + self.cell_size, y1 + self.cell_size
                draw.rectangle([x1, y1, x2, y2], fill=color, outline='black', width=1)

    def _create_april_tag(self, tag_id, size=11):
        """生成模拟 TAG25H9 标签 (11x11)"""
        key = f"tag25h9_{tag_id}"
        if key not in tag_dict:
            raise ValueError(f"JSON 中没有找到 tag_id={tag_id}")
        code_matrix = np.array(tag_dict[key], dtype=np.uint8)

        tag = np.ones((size, size), dtype=np.uint8) * 255
        tag[0, :] = tag[-1, :] = tag[:, 0] = tag[:, -1] = 0
        tag[3:8, 3:8] = code_matrix * 255
        tag[2:9, 2] = tag[2:9, 8] = tag[2, 2:9] = tag[8, 2:9] = 1
        return tag

    def _get_color(self, key):
        """根据键（整数像素值或标记名）返回颜色字符串"""
        if isinstance(key, int):
            return self.color_map.get('grayscale', {}).get(key, 'white')
        return self.color_map.get('markers', {}).get(key, 'white')

    def _draw_colored_rectangle(self, draw, x1, y1, x2, y2, fill_color):
        """绘制带黑色边框的彩色矩形"""
        # 先画边框
        for x in range(x1, x2 + 1):
            draw.rectangle([x * self.cell_size, y1 * self.cell_size,
                           (x + 1) * self.cell_size, (y1 + 1) * self.cell_size], fill='black')
            draw.rectangle([x * self.cell_size, y2 * self.cell_size,
                           (x + 1) * self.cell_size, (y2 + 1) * self.cell_size], fill='black')

        for y in range(y1, y2 + 1):
            draw.rectangle([x1 * self.cell_size, y * self.cell_size,
                           (x1 + 1) * self.cell_size, (y + 1) * self.cell_size], fill='black')
            draw.rectangle([x2 * self.cell_size, y * self.cell_size,
                           (x2 + 1) * self.cell_size, (y + 1) * self.cell_size], fill='black')

        # 填充内部
        for x in range(x1 + 1, x2):
            for y in range(y1 + 1, y2):
                draw.rectangle([x * self.cell_size, y * self.cell_size,
                               (x + 1) * self.cell_size, (y + 1) * self.cell_size],
                               fill=fill_color)

    def _draw_colored_rectangles(self, draw):
        """绘制四组彩色矩形"""
        self._draw_colored_rectangle(draw, 17, 5, 36, 11, self._get_color('color1'))
        self._draw_colored_rectangle(draw, 5, 17, 11, 36, self._get_color('color2'))
        self._draw_colored_rectangle(draw, 17, 42, 36, 48, self._get_color('color3'))
        self._draw_colored_rectangle(draw, 42, 17, 48, 36, self._get_color('color4'))

    def _draw_black_border(self, draw, x1, y1, x2, y2):
        """绘制黑色矩形边框"""
        for i in range(y1, y2):
            draw.rectangle([x1 * self.cell_size, i * self.cell_size,
                           (x1 + 1) * self.cell_size, (i + 1) * self.cell_size], fill='black')
            draw.rectangle([x2 * self.cell_size, i * self.cell_size,
                           (x2 + 1) * self.cell_size, (i + 2) * self.cell_size], fill='black')

        for i in range(x1, x2):
            draw.rectangle([i * self.cell_size, y1 * self.cell_size,
                           (i + 1) * self.cell_size, (y1 + 1) * self.cell_size], fill='black')
            draw.rectangle([i * self.cell_size, y2 * self.cell_size,
                           (i + 2) * self.cell_size, (y2 + 1) * self.cell_size], fill='black')

    def _draw_center_digit(self, draw, digit):
        """绘制中心数字"""
        try:
            font = ImageFont.truetype("arial.ttf", 20 * self.cell_size)
        except:
            font = ImageFont.load_default()

        center_x = (17 + 38) // 2 * self.cell_size + self.cell_size // 2
        center_y = (17 + 38) // 2 * self.cell_size + self.cell_size // 2
        draw.text((center_x, center_y), str(digit),
                  font=font, fill='black', anchor='mm')

    def generate_feature_map(self, output_path, center_digit=5):
        """生成特征图"""
        img = Image.new('RGB', (self.img_size, self.img_size), color='white')
        draw = ImageDraw.Draw(img)

        self._draw_grid(draw)
        # 四角 AprilTag
        self._draw_april_tag(draw, 0, 0, 0)
        self._draw_april_tag(draw, 1, self.grid_size - 11, 0)
        self._draw_april_tag(draw, 2, 0, self.grid_size - 11)
        self._draw_april_tag(draw, 3, self.grid_size - 11, self.grid_size - 11)
        # 彩色矩形
        self._draw_colored_rectangles(draw)
        # 黑框 (12,12)-(43,43)
        self._draw_black_border(draw, 11, 11, 42, 42)
        # 中心黑框 + 白色内框
        # 4. 绘制(16,16)-(39,39)的黑色矩形
        # 先填充整个矩形为黑色
        for x in range(15, 39):  # 16到39（包含）
            for y in range(15, 39):
                draw.rectangle([x*self.cell_size, y*self.cell_size, 
                            (x+1)*self.cell_size, (y+1)*self.cell_size], 
                            fill='black')
        
        # 擦去(19,19)-(36,36)的黑色部分（改为白色）
        for x in range(18, 36):  # 19到36（包含）
            for y in range(18, 36):
                draw.rectangle([x*self.cell_size, y*self.cell_size, 
                            (x+1)*self.cell_size, (y+1)*self.cell_size], 
                            fill='white')
        # 中心数字
        self._draw_center_digit(draw, center_digit)

        img.save(output_path)
        print(f"特征图已保存至: {output_path}")
        return img


if __name__ == "__main__":
    
    # 自定义颜色映射
    color_map = {
        'grayscale': {
            0: 'black',
            1: 'black',
            2: 'gray',
            255: 'white'
        },
        'markers': {
            'color1': 'green',
            'color2': 'green',
            'color3': 'green',
            'color4': 'green'
        }
    }
    
    # 自定义中心数字
    center_digit = 5  # 中心数字
    
    gen = FeatureMapGenerator(color_map=color_map)
    gen.generate_feature_map("feature_map.png", center_digit=center_digit)
