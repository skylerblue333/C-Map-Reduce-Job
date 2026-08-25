#include "map_reduce.h"

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static size_t bounded_strlen(const char *value, size_t max_len) {
    size_t len = 0U;
    if (value == NULL) return 0U;
    while (len <= max_len && value[len] != '\0') ++len;
    return len;
}

static int entry_compare(const void *left, const void *right) {
    const sky_mr_entry *a = (const sky_mr_entry *)left;
    const sky_mr_entry *b = (const sky_mr_entry *)right;
    return strcmp(a->token, b->token);
}

static sky_mr_result add_token(sky_mr_result_set *out, const char *token) {
    size_t i;
    for (i = 0U; i < out->size; ++i) {
        if (strcmp(out->entries[i].token, token) == 0) {
            if (out->entries[i].count == ULONG_MAX) return SKY_MR_CAPACITY_EXCEEDED;
            out->entries[i].count++;
            out->token_count++;
            return SKY_MR_OK;
        }
    }

    if (out->size >= SKY_MR_MAX_UNIQUE) return SKY_MR_CAPACITY_EXCEEDED;
    memcpy(out->entries[out->size].token, token, strlen(token) + 1U);
    out->entries[out->size].count = 1UL;
    out->size++;
    out->token_count++;
    return SKY_MR_OK;
}

sky_mr_result sky_mr_word_count(const char *const *inputs, size_t input_count, sky_mr_result_set *out) {
    size_t input_index;

    if (inputs == NULL || out == NULL || input_count == 0U || input_count > SKY_MR_MAX_INPUTS) {
        return SKY_MR_INVALID_INPUT;
    }
    memset(out, 0, sizeof(*out));
    out->input_count = input_count;

    for (input_index = 0U; input_index < input_count; ++input_index) {
        const char *text = inputs[input_index];
        const size_t text_len = bounded_strlen(text, SKY_MR_MAX_TEXT);
        size_t pos = 0U;

        if (text == NULL || text_len > SKY_MR_MAX_TEXT) return SKY_MR_INVALID_INPUT;
        while (pos < text_len) {
            char token[SKY_MR_MAX_TOKEN + 1U];
            size_t token_len = 0U;

            while (pos < text_len && !isalnum((unsigned char)text[pos])) ++pos;
            while (pos < text_len && isalnum((unsigned char)text[pos])) {
                if (token_len >= SKY_MR_MAX_TOKEN) return SKY_MR_INVALID_INPUT;
                token[token_len++] = (char)tolower((unsigned char)text[pos++]);
            }
            if (token_len > 0U) {
                sky_mr_result result;
                token[token_len] = '\0';
                result = add_token(out, token);
                if (result != SKY_MR_OK) return result;
            }
        }
    }

    qsort(out->entries, out->size, sizeof(out->entries[0]), entry_compare);
    return SKY_MR_OK;
}

const sky_mr_entry *sky_mr_find(const sky_mr_result_set *result, const char *token) {
    size_t i;
    if (result == NULL || token == NULL) return NULL;
    for (i = 0U; i < result->size; ++i) {
        if (strcmp(result->entries[i].token, token) == 0) return &result->entries[i];
    }
    return NULL;
}

const char *sky_mr_result_string(sky_mr_result result) {
    switch (result) {
        case SKY_MR_OK: return "ok";
        case SKY_MR_INVALID_INPUT: return "invalid_input";
        case SKY_MR_CAPACITY_EXCEEDED: return "capacity_exceeded";
        default: return "unknown";
    }
}
