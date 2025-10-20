#ifndef COLORS_H
#define COLORS_H

// Reset
#define COLOR_RESET "\033[0m"

// Regular colors
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// Bright colors
#define COLOR_BRIGHT_BLACK "\033[90m"
#define COLOR_BRIGHT_RED "\033[91m"
#define COLOR_BRIGHT_GREEN "\033[92m"
#define COLOR_BRIGHT_YELLOW "\033[93m"
#define COLOR_BRIGHT_BLUE "\033[94m"
#define COLOR_BRIGHT_MAGENTA "\033[95m"
#define COLOR_BRIGHT_CYAN "\033[96m"
#define COLOR_BRIGHT_WHITE "\033[97m"

// Background colors
#define COLOR_BG_BLACK "\033[40m"
#define COLOR_BG_RED "\033[41m"
#define COLOR_BG_GREEN "\033[42m"
#define COLOR_BG_YELLOW "\033[43m"
#define COLOR_BG_BLUE "\033[44m"
#define COLOR_BG_MAGENTA "\033[45m"
#define COLOR_BG_CYAN "\033[46m"
#define COLOR_BG_WHITE "\033[47m"

// Bright background colors
#define COLOR_BG_BRIGHT_BLACK "\033[100m"
#define COLOR_BG_BRIGHT_RED "\033[101m"
#define COLOR_BG_BRIGHT_GREEN "\033[102m"
#define COLOR_BG_BRIGHT_YELLOW "\033[103m"
#define COLOR_BG_BRIGHT_BLUE "\033[104m"
#define COLOR_BG_BRIGHT_MAGENTA "\033[105m"
#define COLOR_BG_BRIGHT_CYAN "\033[106m"
#define COLOR_BG_BRIGHT_WHITE "\033[107m"

// Text styles
#define STYLE_BOLD "\033[1m"
#define STYLE_DIM "\033[2m"
#define STYLE_ITALIC "\033[3m"
#define STYLE_UNDERLINE "\033[4m"
#define STYLE_BLINK "\033[5m"
#define STYLE_REVERSE "\033[7m"
#define STYLE_HIDDEN "\033[8m"
#define STYLE_STRIKETHROUGH "\033[9m"

// Cursor control
#define CURSOR_HOME "\033[H"
#define CLEAR_SCREEN "\033[2J"
#define CLEAR_LINE "\033[2K"

#endif // COLORS_H