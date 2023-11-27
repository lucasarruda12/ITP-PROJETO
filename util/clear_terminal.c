#ifdef _WIN32
#include <stdlib.h>
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

void clear_terminal() {
    system(CLEAR_SCREEN);
}