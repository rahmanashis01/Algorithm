#include <stdio.h>

int is_palindrome(char *str, int left, int right) {
    if (left >= right) {
        return 1;
    }

    if (str[left] != str[right]) {
        return 0;
    }

    return is_palindrome(str, left + 1, right - 1);
}

static int string_length(const char *str) {
    int length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int main(void) {
    char str[256];
    int length;

    if (scanf("%255s", str) != 1) {
        return 1;
    }

    length = string_length(str);

    printf("Raw input string: %s\n", str);
    printf("Palindrome: %d\n", is_palindrome(str, 0, length - 1));

    return 0;
}
