#ifndef _PROMPT
#define _PROMPT

#include <bits/stdc++.h>

int prompt_read_int(const char *prompt) {
    printf("%s", prompt);
    int x;
    scanf("%d", &x);
    return x;
}

std::string prompt_read_name(const char *prompt) {
    printf("%s", prompt);
    std::string x;
    std::cin >> x;
    return x;
}

void prompt_message(const char *prompt) {
    puts(prompt);
}

#endif
