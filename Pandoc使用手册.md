# 📚 Pandoc Markdown 转 PDF 使用手册

## 快速使用

```bash
pandoc "C 语言三周入门.md" -o "C语言三周入门_完整版.pdf" --pdf-engine=xelatex --toc --toc-depth=3 --highlight-style=tango -V CJKmainfont="Microsoft YaHei" -V mainfont="Consolas" -V monofont="Consolas" -V fontsize=12pt -V geometry:margin=1in --include-in-header=emoji-header.tex
```

## 一、简介

Pandoc 是一个强大的文档转换工具，被称为"文档转换的瑞士军刀"。它支持多种文档格式之间的转换，特别适合将 Markdown 文件转换为高质量的 PDF 文档。

### 1.1 为什么选择 Pandoc？

- ✅ **格式丰富**：支持 Markdown、HTML、LaTeX、Word、PDF 等 40+ 种格式
- ✅ **高度自定义**：支持模板、样式、字体等深度定制
- ✅ **跨平台**：支持 Windows、macOS、Linux
- ✅ **开源免费**：完全免费，社区活跃
- ✅ **专业排版**：基于 LaTeX 引擎，输出质量媲美专业出版物

---

## 二、环境准备

### 2.1 安装 Pandoc

#### Windows 系统

**方法一：使用安装包（推荐）**

1. 访问 Pandoc 官网：<https://pandoc.org/installing.html>
2. 下载 Windows 安装包（.msi 文件）
3. 双击运行安装程序，按提示完成安装

**方法二：使用包管理器**

```powershell
# 使用 Chocolatey
choco install pandoc

# 使用 Scoop
scoop install pandoc
```

#### macOS 系统

```bash
# 使用 Homebrew
brew install pandoc
```

#### Linux 系统

```bash
# Ubuntu/Debian
sudo apt-get install pandoc

# Fedora
sudo dnf install pandoc

# Arch Linux
sudo pacman -S pandoc
```

### 2.2 安装 LaTeX 引擎

Pandoc 需要 LaTeX 引擎来生成 PDF。推荐使用 **XeLaTeX**（支持中文）。

#### Windows 系统

**安装 TeX Live（推荐）**

1. 访问：<https://tug.org/texlive/acquire-netinstall.html>
2. 下载 `install-tl-windows.exe`
3. 运行安装程序，选择完整安装（约 7GB）
4. 安装过程可能需要 1-2 小时

**或安装 MiKTeX（轻量级）**

1. 访问：<https://miktex.org/download>
2. 下载并安装 MiKTeX
3. 首次使用时会自动下载所需包

#### macOS 系统

```bash
# 安装 MacTeX
brew install --cask mactex
```

#### Linux 系统

```bash
# Ubuntu/Debian
sudo apt-get install texlive-xetex texlive-latex-extra

# Fedora
sudo dnf install texlive-scheme-full
```

### 2.3 验证安装

```bash
# 检查 Pandoc 版本
pandoc --version

# 检查 XeLaTeX 版本
xelatex --version
```

如果都能正常输出版本信息，说明安装成功。

---

## 三、基础用法

### 3.1 最简单的转换

将 Markdown 文件转换为 PDF：

```bash
pandoc input.md -o output.pdf
```

### 3.2 指定 PDF 引擎

```bash
# 使用 XeLaTeX（推荐，支持中文）
pandoc input.md -o output.pdf --pdf-engine=xelatex

# 使用 PDFLaTeX（仅英文）
pandoc input.md -o output.pdf --pdf-engine=pdflatex

# 使用 LuaLaTeX
pandoc input.md -o output.pdf --pdf-engine=lualatex
```

### 3.3 添加元数据

在 Markdown 文件开头添加 YAML 元数据：

```yaml
---
title: "我的文档标题"
author: "作者姓名"
date: "2025-10-17"
---

# 第一章

正文内容...
```

或通过命令行参数指定：

```bash
pandoc input.md -o output.pdf \
  --metadata title="我的文档" \
  --metadata author="张三"
```

---

## 四、中文支持配置

### 4.1 设置中文字体

Windows 系统常用中文字体：

```bash
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  -V CJKmainfont="Microsoft YaHei"
```

macOS 系统常用中文字体：

```bash
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  -V CJKmainfont="PingFang SC"
```

Linux 系统常用中文字体：

```bash
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  -V CJKmainfont="Noto Sans CJK SC"
```

### 4.2 常用中文字体列表

| 操作系统 | 字体名称 | 说明 |
|---------|---------|------|
| Windows | Microsoft YaHei | 微软雅黑 |
| Windows | SimSun | 宋体 |
| Windows | SimHei | 黑体 |
| Windows | KaiTi | 楷体 |
| macOS | PingFang SC | 苹方-简 |
| macOS | STSong | 华文宋体 |
| macOS | STHeiti | 华文黑体 |
| Linux | Noto Sans CJK SC | 思源黑体 |
| Linux | Noto Serif CJK SC | 思源宋体 |

---

## 五、高级选项

### 5.1 页面设置

```bash
# 设置页边距
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  -V geometry:margin=1in

# 设置纸张大小
pandoc input.md -o output.pdf \
  -V papersize=a4

# 设置字体大小
pandoc input.md -o output.pdf \
  -V fontsize=12pt
```

### 5.2 添加目录

```bash
# 添加目录
pandoc input.md -o output.pdf --toc

# 设置目录深度
pandoc input.md -o output.pdf --toc --toc-depth=2

# 添加章节编号
pandoc input.md -o output.pdf --toc -N
```

### 5.3 代码高亮

```bash
# 启用语法高亮（默认主题）
pandoc input.md -o output.pdf --highlight-style=pygments

# 使用其他主题
pandoc input.md -o output.pdf --highlight-style=tango
pandoc input.md -o output.pdf --highlight-style=kate
pandoc input.md -o output.pdf --highlight-style=monochrome
pandoc input.md -o output.pdf --highlight-style=zenburn

# 禁用语法高亮
pandoc input.md -o output.pdf --no-highlight
```

### 5.4 自定义字体

```bash
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  -V CJKmainfont="Microsoft YaHei" \
  -V mainfont="Times New Roman" \
  -V monofont="Consolas"
```

参数说明：

- `CJKmainfont`：中文字体
- `mainfont`：英文正文字体
- `monofont`：等宽字体（用于代码）

---

## 六、使用自定义样式

### 6.1 创建自定义 LaTeX 配置文件

创建 `custom-header.tex` 文件：

```latex
% 移除章节编号
\setcounter{secnumdepth}{0}

% 设置超链接样式
\usepackage{hyperref}
\hypersetup{
    colorlinks=true,
    linkcolor=blue,
    urlcolor=blue
}

% 设置代码块样式
\usepackage{listings}
\usepackage{xcolor}
\definecolor{codebackground}{RGB}{248,248,248}
\lstset{
    backgroundcolor=\color{codebackground},
    frame=single,
    basicstyle=\ttfamily\small,
    breaklines=true
}
```

### 6.2 使用自定义配置

```bash
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  --include-in-header=custom-header.tex \
  -V CJKmainfont="Microsoft YaHei"
```

---

## 七、完整示例

### 7.1 基础中文 PDF

```bash
pandoc "C 语言入门.md" -o "C语言入门.pdf" \
  --pdf-engine=xelatex \
  -V CJKmainfont="Microsoft YaHei" \
  -V mainfont="Times New Roman" \
  -V fontsize=12pt \
  -V geometry:margin=1in
```

### 7.2 带目录和语法高亮

```bash
pandoc "教程.md" -o "教程.pdf" \
  --pdf-engine=xelatex \
  --toc \
  --toc-depth=3 \
  --highlight-style=tango \
  -V CJKmainfont="Microsoft YaHei" \
  -V mainfont="Consolas" \
  -V fontsize=12pt \
  -V geometry:margin=1in
```

### 7.3 完整配置示例

```bash
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  --toc \
  --toc-depth=3 \
  --highlight-style=tango \
  -V CJKmainfont="Microsoft YaHei" \
  -V mainfont="Consolas" \
  -V monofont="Consolas" \
  -V fontsize=12pt \
  -V geometry:margin=1in \
  -V papersize=a4 \
  --include-in-header=custom-header.tex \
  --metadata title="完整示例文档" \
  --metadata author="作者姓名" \
  --metadata date="2025-10-17"
```

---

## 八、常见问题与解决方案

### 8.1 中文显示为方框或乱码

**原因**：未正确设置中文字体。

**解决方案**：

```bash
# 确保使用 XeLaTeX
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  -V CJKmainfont="Microsoft YaHei"

# 检查系统中可用的中文字体
fc-list :lang=zh
```

### 8.2 找不到字体错误

**错误信息**：`! Package fontspec Error: The font "xxx" cannot be found.`

**解决方案**：

1. 确认字体名称拼写正确
2. 使用系统中已安装的字体
3. 安装缺失的字体

### 8.3 Emoji 或特殊字符不显示

**解决方案**：创建 `emoji-header.tex`：

```latex
\usepackage{newunicodechar}
\newfontfamily\DejaSans{Segoe UI Emoji}

\newunicodechar{💻}{{\DejaSans 💻}}
\newunicodechar{✅}{{\DejaSans ✅}}
\newunicodechar{📚}{{\DejaSans 📚}}
```

使用时：

```bash
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  --include-in-header=emoji-header.tex
```

### 8.4 编译超时或内存不足

**解决方案**：

1. 分割大文件
2. 减少图片数量和大小
3. 使用更简单的 LaTeX 模板

### 8.5 代码块显示问题

**问题**：代码块换行混乱或字体太小。

**解决方案**：在 `custom-header.tex` 中设置：

```latex
\usepackage{fancyvrb}
\DefineVerbatimEnvironment{Highlighting}{Verbatim}{
    breaklines=true,
    fontsize=\normalsize
}
```

---

## 九、批量转换脚本

### 9.1 Windows PowerShell 脚本

创建 `convert-all.ps1`：

```powershell
# 获取所有 Markdown 文件
$mdFiles = Get-ChildItem -Filter "*.md"

foreach ($file in $mdFiles) {
    $outputFile = $file.BaseName + ".pdf"
    Write-Host "正在转换: $($file.Name) -> $outputFile" -ForegroundColor Green
    
    pandoc $file.Name -o $outputFile `
        --pdf-engine=xelatex `
        --toc `
        --highlight-style=tango `
        -V CJKmainfont="Microsoft YaHei" `
        -V fontsize=12pt `
        -V geometry:margin=1in
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✓ 转换成功: $outputFile" -ForegroundColor Green
    } else {
        Write-Host "✗ 转换失败: $($file.Name)" -ForegroundColor Red
    }
}
```

运行：

```powershell
.\convert-all.ps1
```

### 9.2 Linux/macOS Bash 脚本

创建 `convert-all.sh`：

```bash
#!/bin/bash

for file in *.md; do
    output="${file%.md}.pdf"
    echo "正在转换: $file -> $output"
    
    pandoc "$file" -o "$output" \
        --pdf-engine=xelatex \
        --toc \
        --highlight-style=tango \
        -V CJKmainfont="Noto Sans CJK SC" \
        -V fontsize=12pt \
        -V geometry:margin=1in
    
    if [ $? -eq 0 ]; then
        echo "✓ 转换成功: $output"
    else
        echo "✗ 转换失败: $file"
    fi
done
```

运行：

```bash
chmod +x convert-all.sh
./convert-all.sh
```

---

## 十、进阶技巧

### 10.1 使用 Makefile 自动化

创建 `Makefile`：

```makefile
# 配置变量
PANDOC = pandoc
PDF_ENGINE = xelatex
CJK_FONT = Microsoft YaHei
FONT_SIZE = 12pt

# 查找所有 Markdown 文件
SOURCES := $(wildcard *.md)
PDFS := $(SOURCES:.md=.pdf)

# 默认目标
all: $(PDFS)

# 转换规则
%.pdf: %.md
 $(PANDOC) $< -o $@ \
  --pdf-engine=$(PDF_ENGINE) \
  --toc \
  --highlight-style=tango \
  -V CJKmainfont="$(CJK_FONT)" \
  -V fontsize=$(FONT_SIZE) \
  -V geometry:margin=1in

# 清理生成文件
clean:
 rm -f $(PDFS)

.PHONY: all clean
```

使用：

```bash
# 转换所有文件
make

# 清理生成的 PDF
make clean
```

### 10.2 创建可复用的配置文件

创建 `defaults.yaml`：

```yaml
# Pandoc 默认配置
from: markdown
to: pdf
pdf-engine: xelatex

# 输出选项
standalone: true
toc: true
toc-depth: 3
number-sections: false

# 语法高亮
highlight-style: tango

# 字体设置
variables:
  CJKmainfont: Microsoft YaHei
  mainfont: Consolas
  monofont: Consolas
  fontsize: 12pt
  geometry: margin=1in
  papersize: a4

# 自定义 LaTeX
include-in-header:
  - custom-header.tex
```

使用配置文件：

```bash
pandoc input.md -o output.pdf --defaults=defaults.yaml
```

### 10.3 添加水印

在 `custom-header.tex` 中添加：

```latex
\usepackage{draftwatermark}
\SetWatermarkText{草稿}
\SetWatermarkScale{3}
\SetWatermarkLightness{0.9}
```

---

## 十一、性能优化建议

### 11.1 加速编译

1. **使用缓存**：保留中间文件以便增量编译
2. **减少包含内容**：只引入需要的 LaTeX 包
3. **优化图片**：压缩图片大小，使用适当分辨率

### 11.2 减少文件大小

```bash
# 使用 PDF 压缩
pandoc input.md -o output.pdf --pdf-engine=xelatex
gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 \
   -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH \
   -sOutputFile=output-compressed.pdf output.pdf
```

---

## 十二、参考资源

### 12.1 官方文档

- **Pandoc 官方网站**：<https://pandoc.org/>
- **Pandoc 用户手册**：<https://pandoc.org/MANUAL.html>
- **LaTeX 文档**：<https://www.latex-project.org/>

### 12.2 社区资源

- **Pandoc GitHub**：<https://github.com/jgm/pandoc>
- **Stack Overflow**：<https://stackoverflow.com/questions/tagged/pandoc>
- **LaTeX Stack Exchange**：<https://tex.stackexchange.com/>

### 12.3 推荐工具

- **VSCode 插件**：Markdown Preview Enhanced
- **在线编辑器**：<https://pandoc.org/try/>
- **Markdown 编辑器**：Typora、Obsidian、VS Code

---

## 十三、快速参考

### 13.1 常用命令速查

```bash
# 基础转换
pandoc input.md -o output.pdf

# 中文支持
pandoc input.md -o output.pdf --pdf-engine=xelatex -V CJKmainfont="Microsoft YaHei"

# 添加目录
pandoc input.md -o output.pdf --toc

# 语法高亮
pandoc input.md -o output.pdf --highlight-style=tango

# 自定义样式
pandoc input.md -o output.pdf --include-in-header=custom.tex

# 完整配置
pandoc input.md -o output.pdf \
  --pdf-engine=xelatex \
  --toc \
  --highlight-style=tango \
  -V CJKmainfont="Microsoft YaHei" \
  -V fontsize=12pt \
  -V geometry:margin=1in
```

### 13.2 常用参数列表

| 参数 | 说明 | 示例 |
|-----|------|------|
| `-o` | 输出文件 | `-o output.pdf` |
| `--pdf-engine` | PDF 引擎 | `--pdf-engine=xelatex` |
| `--toc` | 生成目录 | `--toc` |
| `--toc-depth` | 目录深度 | `--toc-depth=3` |
| `-N` | 章节编号 | `-N` |
| `--highlight-style` | 代码高亮主题 | `--highlight-style=tango` |
| `-V` | 设置变量 | `-V fontsize=12pt` |
| `--include-in-header` | 包含头文件 | `--include-in-header=custom.tex` |
| `--metadata` | 设置元数据 | `--metadata title="标题"` |

---

## 附录：完整配置文件示例

### emoji-header.tex

```latex
% Emoji 和特殊字符字体支持
\usepackage{newunicodechar}
\newfontfamily\DejaSans{Segoe UI Emoji}
\newfontfamily\TreeFont{DejaVu Sans Mono}

% 定义 emoji 字符
\newunicodechar{💻}{{\DejaSans 💻}}
\newunicodechar{✅}{{\DejaSans ✅}}
\newunicodechar{🌟}{{\DejaSans 🌟}}
\newunicodechar{📘}{{\DejaSans 📘}}
\newunicodechar{🔗}{{\DejaSans 🔗}}
\newunicodechar{📝}{{\DejaSans 📝}}
\newunicodechar{💪}{{\DejaSans 💪}}
\newunicodechar{📚}{{\DejaSans 📚}}

% 定义树形图字符
\newunicodechar{─}{{\TreeFont ─}}
\newunicodechar{│}{{\TreeFont │}}
\newunicodechar{├}{{\TreeFont ├}}
\newunicodechar{└}{{\TreeFont └}}

% 移除章节编号
\setcounter{secnumdepth}{0}

% 设置更大的字体
\renewcommand{\normalsize}{\fontsize{12pt}{18pt}\selectfont}

% 超链接样式 - 蓝色带下划线
\usepackage{hyperref}
\usepackage[normalem]{ulem}
\hypersetup{
    colorlinks=true,
    linkcolor=blue,
    urlcolor=blue,
    bookmarks=true
}
\makeatletter
\Hy@colorlinkstrue
\def\Hy@colorlink#1{%
  \begingroup
    \color{#1}%
    \uline
}
\def\Hy@endcolorlink{%
  \endgroup
}
\makeatother

% 代码块样式
\usepackage{listings}
\usepackage{xcolor}
\definecolor{codebackground}{RGB}{248,248,248}
\definecolor{codeborder}{RGB}{204,204,204}
\lstdefinestyle{mystyle}{
    backgroundcolor=\color{codebackground},
    frame=single,
    rulecolor=\color{codeborder},
    basicstyle=\ttfamily\normalsize,
    breaklines=true
}
\lstset{style=mystyle}
```

---

**文档版本**：v1.0  
**最后更新**：2025-10-17  
**作者**：AI Assistant

💡 **提示**：建议将本手册保存为 PDF，方便随时查阅！

```bash
pandoc Pandoc使用手册.md -o Pandoc使用手册.pdf \
  --pdf-engine=xelatex \
  --toc \
  --toc-depth=3 \
  --highlight-style=tango \
  -V CJKmainfont="Microsoft YaHei" \
  -V fontsize=11pt \
  -V geometry:margin=1in
```
