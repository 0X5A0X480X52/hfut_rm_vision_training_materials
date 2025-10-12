import pandas as pd

# 执行前请确保已安装 pandas 库
# 如果未安装，请使用以下命令进行安装：
# pip install pandas

# 1) 读取 CSV（建议文件保存为 UTF-8 或 UTF-8-SIG）
# 【注】执行时请确保文件路径正确，可使用绝对路径或相对路径
df = pd.read_csv(r"code\第三次培训\grades.csv", encoding="utf-8-sig")

# 2) 标准化列名（去除首尾空白，防止列名中有不可见字符）
df.columns = df.columns.str.strip()

# 3) 强制将关键列转换为数值（无法转换的值变为 NaN）
for col in ["学分", "绩点", "成绩"]:
    df[col] = pd.to_numeric(df[col], errors="coerce")

# 4) 丢弃关键字段缺失的行（学分/绩点/成绩任意缺失则删除）
df_valid = df.dropna(subset=["学分", "绩点", "成绩"]).copy()

# 5) 如果没有有效行或总学分为 0，则给出提示
total_credit = df_valid["学分"].sum()
if total_credit == 0 or len(df_valid) == 0:
    print("没有有效的成绩数据或总学分为 0，无法计算加权平均。")
else:
    # 6) 计算加权和并除以总学分
    weighted_gpa = (df_valid["绩点"] * df_valid["学分"]).sum() / total_credit
    weighted_score = (df_valid["成绩"] * df_valid["学分"]).sum() / total_credit

    # 7) 可选：展示每门课程对总和的贡献，便于讲解
    df_valid["绩点×学分"] = df_valid["绩点"] * df_valid["学分"]
    df_valid["成绩×学分"] = df_valid["成绩"] * df_valid["学分"]

    # 打印结果（保留两位小数）
    print(f"总学分: {total_credit:.1f}")
    print(f"加权平均绩点: {weighted_gpa:.2f}")
    print(f"加权平均成绩: {weighted_score:.2f}")
    print("\n每门课程贡献（部分列展示）：")
    print(df_valid[["课程名称", "学分", "绩点", "成绩", "绩点×学分", "成绩×学分"]].head().to_string(index=False))