#pragma once
#include <windows.h>

bool hideInputEcho(bool flag) {  // 就...挺酷的
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    if (flag) {
        mode &= (~ENABLE_ECHO_INPUT);
    } else {
        mode |= ENABLE_ECHO_INPUT;
    }
    return (bool)SetConsoleMode(hStdin, mode);
}
