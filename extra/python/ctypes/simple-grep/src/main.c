#include <stdio.h>
#include "simple_grep.h"
#define MIN_ARGS    3
#define ARGS_ERROR -1
#define FILE_ARG    1
#define EXPR_ARG    2

int main(int argc, char** argv) {
	if (argc < MIN_ARGS) {
		printf("Uso: %s, <file> <expr>", argv[0]);
		return ARGS_ERROR;
	}
	FILE* fd = fopen(argv[FILE_ARG], "r");
	simple_grep(fd, argv[EXPR_ARG]);
	return 0;
}