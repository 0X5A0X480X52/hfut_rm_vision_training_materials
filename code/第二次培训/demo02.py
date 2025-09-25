# while 示例
count = 0
while count <= 5:
    print("循环次数:", count)
    count = count + 1

    if count == 2:
        print("跳过本次循环")
        continue

    if count == 3:
        print("退出循环")
        break

    print("当前 count 值:", count)