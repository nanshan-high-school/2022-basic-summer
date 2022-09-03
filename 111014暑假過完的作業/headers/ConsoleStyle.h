#pragma once

#ifdef _WIN32
#define ESCAPE "\x1b["
#endif

#ifdef _WIN64
#define ESCAPE "\x1b["
#endif

#ifdef linux
#define ESCAPE "\033["
#endif

#ifdef __unix__
#define ESCAPE "\033["
#endif

#define RESET_COLOR ESCAPE "0m"
#define BOLD ESCAPE "1m"
#define REMOVE_BOLD ESCAPE "22m"
#define UNDERLINE ESCAPE "4m"
#define REMOVE_UNDERLINE ESCAPE "24m"
#define SWAP_FG_BG ESCAPE "7m"

#define FG_BLACK ESCAPE "30m"
#define FG_RED ESCAPE "31m"
#define FG_GREEN ESCAPE "32m"
#define FG_YELLOW ESCAPE "33m"
#define FG_BLUE ESCAPE "34m"
#define FG_MAGENTA ESCAPE "35m"
#define FG_CYAN ESCAPE "36m"
#define FG_WHITE ESCAPE "37m"
#define FG_RESET ESCAPE "39m"
#define FG_SET_RGB(r, g, b) ESCAPE "38;2;" r ";" g ";" b

#define BG_BLACK ESCAPE "40m"
#define BG_RED ESCAPE "41m"
#define BG_GREEN ESCAPE "42m"
#define BG_YELLOW ESCAPE "43m"
#define BG_BLUE ESCAPE "44m"
#define BG_MAGENTA ESCAPE "45m"
#define BG_CYAN ESCAPE "46m"
#define BG_WHITE ESCAPE "47m"
#define BG_RESET ESCAPE "49m"
#define BG_SET_RGB(r, g, b) ESCAPE "48;2;" r ";" g ";" b
