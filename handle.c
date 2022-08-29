#include "handle.h"
#include <stdio.h>
#include <stdlib.h>

unsigned get_unsigned() {
    char input[128];
    fgets(input, 128, stdin);
    if (input[0] == '\n') {
        printf("Incorrect input. Enter again: ");
        return -1;
    }
    int minus_count = 0;
    int number_count = 0;
    int i = 0;
    for (; input[i] != '\n' && input[i] != '\0'; ++i) {
        if (input[i] == '-') {
            ++minus_count;
            continue;
        } else if (input[i] == '+') continue;
        else break;
    }
    if (minus_count % 2 != 0) {
        printf("Incorrect input. Enter again: ");
        return -1;
    } else {
        char *out = malloc(sizeof(char) * strlen(input) - minus_count);
        for (; input[i] != '\n' && input[i] != '\0'; ++i) {
            if (input[i] < '0' || input[i] > '9') {
                printf("Incorrect input. Enter again: ");
                return -1;
            } else {
                out[number_count] = input[i];
                number_count += 1;
            }
            if (number_count > 10) {
                printf("Too big!\nEnter again:");
                free(out);
                return -1;
            }
        }
        out[number_count] = '\0';
        char *stopper;
        unsigned out_u = strtoul(out, &stopper, 10);
        free(out);
        return out_u;
    }
}

char *get_str(const char *label) {
    char *str = malloc(sizeof(char) * 128);
    if (label)
        printf("Enter %s: ", label);
    char sym = '0';
    int count = 0, len = 128;
    while (sym != '\n') {
        sym = getchar();

        if (count == len) {
            len += 128;
            str = realloc(str, sizeof(char) * len);
        }
        if (sym == '\n') {
            str[count] = '\0';
            count += 1;
            break;
        }
        str[count] = sym;
        count += 1;


    }

    return realloc(str, sizeof(char) * count);
}

char *str_dup(const char *srcstr) {
    if (srcstr == NULL)
        return NULL;

    char *str = malloc(sizeof(char) * (strlen(srcstr) + 1));
    strcpy(str, srcstr);

    return str;
}
