#include <stdio.h>

struct Student {
    char name[20];
    int age;
    float score;
};

int main(int argc, char const *argv[])
{
    // 直接访问结构体成员
    struct Student s1 = {"Alice", 20, 88.5};
    printf("Name: %s, Age: %d, Score: %.1f\n", s1.name, s1.age, s1.score);
    
    // 使用指针访问结构体成员
    struct Student *p = &s1;
    printf("%s %d %.1f\n", p->name, p->age, p->score);

    return 0;
}