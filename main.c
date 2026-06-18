#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 4096
#define MAX_LEN 64

typedef struct {
    char word[MAX_LEN];
    int count;
} WordCount;

WordCount results[MAX_WORDS];
int result_size = 0;

void to_lower(char *s) {
    for (; *s; s++) *s = tolower((unsigned char)*s);
}

void map(const char *text) {
    char buf[4096];
    strncpy(buf, text, sizeof(buf) - 1);
    char *token = strtok(buf, " ,.!?;:\n\t\"'");
    while (token) {
        to_lower(token);
        /* Find or insert */
        int found = 0;
        for (int i = 0; i < result_size; i++) {
            if (strcmp(results[i].word, token) == 0) {
                results[i].count++;
                found = 1;
                break;
            }
        }
        if (!found && result_size < MAX_WORDS) {
            strncpy(results[result_size].word, token, MAX_LEN - 1);
            results[result_size].count = 1;
            result_size++;
        }
        token = strtok(NULL, " ,.!?;:\n\t\"'");
    }
}

int cmp_desc(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

void reduce_and_print(int top_n) {
    qsort(results, result_size, sizeof(WordCount), cmp_desc);
    printf("=== Top %d Words ===\n", top_n);
    for (int i = 0; i < top_n && i < result_size; i++) {
        printf("  %-20s %d\n", results[i].word, results[i].count);
    }
}

int main() {
    const char *corpus[] = {
        "the quick brown fox jumps over the lazy dog",
        "the dog barked at the fox and the fox ran away",
        "a quick brown dog outpaces a lazy fox today"
    };
    int n = sizeof(corpus) / sizeof(corpus[0]);
    for (int i = 0; i < n; i++) map(corpus[i]);
    reduce_and_print(10);
    return 0;
}
