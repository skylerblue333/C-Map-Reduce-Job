#include "map_reduce.h"

#include <stdio.h>

int main(void) {
    const char *inputs[] = {
        "Sky systems are bounded systems",
        "Map reduce maps words and reduces counts",
        "Sky map reduce stays deterministic"
    };
    sky_mr_result_set result;
    const sky_mr_result status = sky_mr_word_count(inputs, 3U, &result);
    size_t i;

    if (status != SKY_MR_OK) {
        fprintf(stderr, "map-reduce error: %s\n", sky_mr_result_string(status));
        return 1;
    }

    printf("mode=single_process distributed_execution=false inputs=%zu tokens=%zu unique=%zu\n",
           result.input_count, result.token_count, result.size);
    for (i = 0U; i < result.size; ++i) {
        printf("%s=%lu\n", result.entries[i].token, result.entries[i].count);
    }
    return 0;
}
