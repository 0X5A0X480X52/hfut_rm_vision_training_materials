# OOP 版成绩管理系统
class Student:
    def __init__(self, name, scores):
        self.name = name
        self.scores = scores

    def average(self):
        return sum(self.scores) / len(self.scores)

    def add_bonus(self, bonus):
        self.scores = [s + bonus for s in self.scores]

    def report(self):
        print("-------- 成绩报告 --------")
        print(f"{self.name} 的平均分: {self.average():.1f}")
        print(f"- 成绩列表: {self.scores}")
        print("--------------------------\n")
        
# 创建学生对象
alice = Student("Alice", [80, 90, 70])
print(alice.name)
print(alice.average())
alice.report()

# 使用对象方法
bob = Student("Bob", [60, 65, 70])
bob.report()
print("给 bob 加 5 分奖励")
bob.add_bonus(5)
bob.report()