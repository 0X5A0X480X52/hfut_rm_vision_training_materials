#include <stdio.h>
#include "file_utils.h"

void save_student_to_file(const struct Student *s, const char *path) {
	if (!s || !path) return;
	FILE *f = fopen(path, "w");
	if (!f) return;
	fprintf(f, "%d,%s\n", s->id, s->name);
	fclose(f);
}

