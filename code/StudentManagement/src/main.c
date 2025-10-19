#include <stdio.h>
#include "student.h"
#include "file_utils.h"

int main(void) {
	printf("Student Management - minimal demo\n");

	struct Student s;
	s.id = 1;
	snprintf(s.name, sizeof(s.name), "Alice");

	print_student(&s);

	// 保存并读取示例文件
	save_student_to_file(&s, "students.txt");
	printf("Saved student to students.txt\n");

	return 0;
}

