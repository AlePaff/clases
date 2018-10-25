#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "simple_grep.h"

void simple_grep(FILE* file, char* expr) {
	char* buf = 0;
	int line = 0;
	size_t n = 0;
	while(getline(&buf, &n, file) != -1) {
		if (strstr(buf, expr)) {
			printf("Line %d: %s", line, buf);
		}
		line++;
		n = 0;
	}
	free(buf);
}

void simple_grep_fd(int fd, char* expr) {
	FILE* file = fdopen(fd, "r");
	simple_grep(file, expr);
}
