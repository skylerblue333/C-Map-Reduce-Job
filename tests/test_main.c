#include "map_reduce.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *inputs[] = {
        "Alpha beta ALPHA",
        "beta gamma, alpha"
    };
    sky_mr_result_set result;
    const sky_mr_entry *entry;
    char long_token[SKY_MR_MAX_TOKEN + 2U];
    const char *invalid_inputs[1];

    assert(sky_mr_word_count(inputs, 2U, &result) == SKY_MR_OK);
    assert(result.input_count == 2U);
    assert(result.token_count == 6U);
    assert(result.size == 3U);
    assert(strcmp(result.entries[0].token, "alpha") == 0);
    assert(strcmp(result.entries[1].token, "beta") == 0);
    assert(strcmp(result.entries[2].token, "gamma") == 0);

    entry = sky_mr_find(&result, "alpha");
    assert(entry != NULL && entry->count == 3UL);
    entry = sky_mr_find(&result, "beta");
    assert(entry != NULL && entry->count == 2UL);
    entry = sky_mr_find(&result, "gamma");
    assert(entry != NULL && entry->count == 1UL);
    assert(sky_mr_find(&result, "missing") == NULL);

    assert(sky_mr_word_count(NULL, 1U, &result) == SKY_MR_INVALID_INPUT);
    assert(sky_mr_word_count(inputs, 0U, &result) == SKY_MR_INVALID_INPUT);

    memset(long_token, 'x', sizeof(long_token));
    long_token[sizeof(long_token) - 1U] = '\0';
    invalid_inputs[0] = long_token;
    assert(sky_mr_word_count(invalid_inputs, 1U, &result) == SKY_MR_INVALID_INPUT);

    puts("all map-reduce tests passed");
    return 0;
}
