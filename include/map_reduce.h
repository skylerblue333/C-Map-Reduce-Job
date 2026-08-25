#ifndef SKY_MAP_REDUCE_H
#define SKY_MAP_REDUCE_H

#include <stddef.h>

#define SKY_MR_MAX_INPUTS 256U
#define SKY_MR_MAX_TEXT 4096U
#define SKY_MR_MAX_TOKEN 63U
#define SKY_MR_MAX_UNIQUE 1024U

typedef enum {
    SKY_MR_OK = 0,
    SKY_MR_INVALID_INPUT = -1,
    SKY_MR_CAPACITY_EXCEEDED = -2
} sky_mr_result;

typedef struct {
    char token[SKY_MR_MAX_TOKEN + 1U];
    unsigned long count;
} sky_mr_entry;

typedef struct {
    sky_mr_entry entries[SKY_MR_MAX_UNIQUE];
    size_t size;
    size_t input_count;
    size_t token_count;
} sky_mr_result_set;

sky_mr_result sky_mr_word_count(const char *const *inputs, size_t input_count, sky_mr_result_set *out);
const sky_mr_entry *sky_mr_find(const sky_mr_result_set *result, const char *token);
const char *sky_mr_result_string(sky_mr_result result);

#endif
