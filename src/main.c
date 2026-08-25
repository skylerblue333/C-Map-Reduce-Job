#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_BYTES (1024UL * 1024UL)
#define MAX_UNIQUE_WORDS 1024
#define MAX_WORD_LENGTH 63

typedef struct {
    char word[MAX_WORD_LENGTH + 1];
    uint64_t count;
} word_count_t;

typedef struct {
    word_count_t entries[MAX_UNIQUE_WORDS];
    size_t size;
    uint64_t total_words;
} reducer_t;

static int compare_entries(const void *left, const void *right) {
    const word_count_t *a = (const word_count_t *)left;
    const word_count_t *b = (const word_count_t *)right;
    return strcmp(a->word, b->word);
}

static int reduce_word(reducer_t *reducer, const char *word) {
    size_t i;
    if (reducer == NULL || word == NULL || *word == '\0') {
        return -1;
    }
    for (i = 0; i < reducer->size; ++i) {
        if (strcmp(reducer->entries[i].word, word) == 0) {
            if (reducer->entries[i].count == UINT64_MAX || reducer->total_words == UINT64_MAX) {
                return -1;
            }
            reducer->entries[i].count++;
            reducer->total_words++;
            return 0;
        }
    }
    if (reducer->size >= MAX_UNIQUE_WORDS || reducer->total_words == UINT64_MAX) {
        return -1;
    }
    memcpy(reducer->entries[reducer->size].word, word, strlen(word) + 1);
    reducer->entries[reducer->size].count = 1;
    reducer->size++;
    reducer->total_words++;
    return 0;
}

static int process_file(FILE *input, reducer_t *reducer) {
    unsigned long bytes = 0;
    char word[MAX_WORD_LENGTH + 1];
    size_t length = 0;
    int ch;

    while ((ch = fgetc(input)) != EOF) {
        bytes++;
        if (bytes > MAX_FILE_BYTES) {
            fprintf(stderr, "input exceeds 1 MiB limit\n");
            return -1;
        }
        if (isalnum((unsigned char)ch)) {
            if (length >= MAX_WORD_LENGTH) {
                fprintf(stderr, "word exceeds %d characters\n", MAX_WORD_LENGTH);
                return -1;
            }
            word[length++] = (char)tolower((unsigned char)ch);
        } else if (length != 0) {
            word[length] = '\0';
            if (reduce_word(reducer, word) != 0) {
                fprintf(stderr, "word cardinality/count limit exceeded\n");
                return -1;
            }
            length = 0;
        }
    }

    if (ferror(input)) {
        fprintf(stderr, "failed while reading input\n");
        return -1;
    }
    if (length != 0) {
        word[length] = '\0';
        if (reduce_word(reducer, word) != 0) {
            fprintf(stderr, "word cardinality/count limit exceeded\n");
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    FILE *input;
    reducer_t reducer = {0};
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 2;
    }
    input = fopen(argv[1], "rb");
    if (input == NULL) {
        perror("open input");
        return 1;
    }
    if (process_file(input, &reducer) != 0) {
        fclose(input);
        return 1;
    }
    fclose(input);

    qsort(reducer.entries, reducer.size, sizeof(reducer.entries[0]), compare_entries);
    printf("{\"total_words\":%llu,\"unique_words\":%zu,\"counts\":{",
           (unsigned long long)reducer.total_words, reducer.size);
    for (i = 0; i < reducer.size; ++i) {
        printf("%s\"%s\":%llu", i == 0 ? "" : ",", reducer.entries[i].word,
               (unsigned long long)reducer.entries[i].count);
    }
    puts("}}");
    return 0;
}
