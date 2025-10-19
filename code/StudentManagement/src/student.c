#include <stdio.h>
#include "student.h"

void print_student(const struct Student *s) {
	if (!s) return;
	printf("Student{id=%d, name=%s}\n", s->id, s->name);
}

