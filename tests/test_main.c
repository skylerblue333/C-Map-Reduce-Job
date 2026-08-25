#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static int exit_code(const char *command) {
    const int status = system(command);
    if (status == -1 || !WIFEXITED(status)) {
        return -1;
    }
    return WEXITSTATUS(status);
}

static int expect_exit(const char *command, int expected) {
    const int actual = exit_code(command);
    if (actual != expected) {
        fprintf(stderr, "command failed expectation: %s (expected %d, got %d)\n", command, expected, actual);
        return 1;
    }
    return 0;
}

int main(void) {
    int failures = 0;
    failures += expect_exit("./app ../tests/fixtures/words.txt >/tmp/word-reducer.json", 0);
    failures += expect_exit("grep -q '\"total_words\":5' /tmp/word-reducer.json", 0);
    failures += expect_exit("grep -q '\"unique_words\":3' /tmp/word-reducer.json", 0);
    failures += expect_exit("grep -q '\"alpha\":2' /tmp/word-reducer.json", 0);
    failures += expect_exit("grep -q '\"beta\":2' /tmp/word-reducer.json", 0);
    failures += expect_exit("./app /definitely/missing >/dev/null 2>&1", 1);
    failures += expect_exit("./app >/dev/null 2>&1", 2);
    failures += expect_exit("./app ../tests/fixtures/long-word.txt >/dev/null 2>&1", 1);
    if (failures != 0) {
        return 1;
    }
    puts("word reducer contract tests passed");
    return 0;
}
