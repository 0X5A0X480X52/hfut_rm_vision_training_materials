# 学生成绩管理系统示例

# 1. 变量与运算符
passing_score = 60
bonus = 5
print("及格线:", passing_score, "奖励分:", bonus)

# 2. 输入与输出
name = input("请输入学生姓名: ")
scores_input = input("请输入该学生的成绩（用空格分隔）: ")

# 把输入字符串转为列表（数字），不用列表推导式
scores = []
for x in scores_input.split():
    scores.append(int(x))

# 3. 基本数据结构
# 数字：计算总分、平均分
total = 0
for s in scores:
    total = total + s
average = total / len(scores)

# 列表：存储多门成绩
print("成绩列表:", scores)

# 元组：存储固定信息（姓名, 科目数）
student_info = (name, len(scores))
print("学生信息:", student_info)

# 字典：存储学生的完整档案
student_record = {
    "name": name,
    "scores": scores,
    "average": average
}
print("学生档案:", student_record)

# 集合：去除重复成绩
unique_scores = set(scores)
print("去重后的成绩:", unique_scores)

# 4. 控制流
if average >= passing_score:
    print(name, "平均分及格 🎉")
else:
    print(name, "平均分不及格 😢")

# 5. 函数
def add_bonus(scores, bonus):
    """给所有成绩加上奖励分"""
    new_list = []
    for s in scores:
        new_list.append(s + bonus)
    return new_list

# 调用函数
new_scores = add_bonus(scores, bonus)
print("加分后的成绩:", new_scores)
