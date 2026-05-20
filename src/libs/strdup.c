#include <stdlib.h>
#include <string.h>
char* __strdup(const char* input) {
    if (!input) return NULL;
    size_t newl = strlen(input) + 1;
    char* news = malloc(newl);
    if (!news) return NULL;
    return memcpy(news,input,newl);
}