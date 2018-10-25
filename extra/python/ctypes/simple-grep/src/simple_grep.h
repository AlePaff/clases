#ifndef SIMPLE_GREP
#define SIMPLE_GREP

void simple_grep(FILE* file, char* expr);
void simple_grep_fd(int fd, char* expr);

#endif // SIMPLE_GREP
