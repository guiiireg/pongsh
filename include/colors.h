/**
 * ============================================================================
 *                              COLORS AND THEMES
 * ============================================================================
 * File: colors.h
 * Description: Color definitions and modern characters for shell display.
 * Dependencies: pongsh.h
 * ============================================================================
 */

#ifndef COLORS_H
    #define COLORS_H

    #define _GNU_SOURCE
    #include "pongsh.h"

    // ---- ANSI Color Codes ----
    #define RESET           "\033[0m"
    #define BOLD            "\033[1m"
    #define DIM             "\033[2m"
    #define ITALIC          "\033[3m"
    #define UNDERLINE       "\033[4m"
    #define BLINK           "\033[5m"
    #define REVERSE         "\033[7m"
    #define STRIKETHROUGH   "\033[9m"

    // ---- Foreground Colors ----
    #define BLACK           "\033[30m"
    #define RED             "\033[31m"
    #define GREEN           "\033[32m"
    #define YELLOW          "\033[33m"
    #define BLUE            "\033[34m"
    #define MAGENTA         "\033[35m"
    #define CYAN            "\033[36m"
    #define WHITE           "\033[37m"

    // ---- Bright Foreground Colors ----
    #define BRIGHT_BLACK    "\033[90m"
    #define BRIGHT_RED      "\033[91m"
    #define BRIGHT_GREEN    "\033[92m"
    #define BRIGHT_YELLOW   "\033[93m"
    #define BRIGHT_BLUE     "\033[94m"
    #define BRIGHT_MAGENTA  "\033[95m"
    #define BRIGHT_CYAN     "\033[96m"
    #define BRIGHT_WHITE    "\033[97m"

    // ---- Background Colors ----
    #define BG_BLACK        "\033[40m"
    #define BG_RED          "\033[41m"
    #define BG_GREEN        "\033[42m"
    #define BG_YELLOW       "\033[43m"
    #define BG_BLUE         "\033[44m"
    #define BG_MAGENTA      "\033[45m"
    #define BG_CYAN         "\033[46m"
    #define BG_WHITE        "\033[47m"

    // ---- Modern Unicode Characters ----
    #define ARROW_RIGHT     "➜"
    #define ARROW_LEFT      "←"
    #define ARROW_UP        "↑"
    #define ARROW_DOWN      "↓"
    #define TRIANGLE_RIGHT  "▶"
    #define TRIANGLE_LEFT   "◀"
    #define CIRCLE_FILLED   "●"
    #define CIRCLE_EMPTY    "○"
    #define SQUARE_FILLED   "■"
    #define SQUARE_EMPTY    "□"
    #define DIAMOND         "◆"
    #define STAR            "★"
    #define HEART           "♥"
    #define LIGHTNING       "⚡"
    #define FOLDER          "📁"
    #define FILE            "📄"
    #define GEAR            "⚙"
    #define CHECK_MARK      "✓"
    #define CROSS_MARK      "✗"
    #define WARNING         "⚠"
    #define INFO            "ℹ"
    #define BRANCH          "⎇"
    #define HOME            "🏠"
    #define TERMINAL        "💻"

    // ---- Shell Theme Colors ----
    #define PROMPT_USER     BRIGHT_GREEN
    #define PROMPT_HOST     BRIGHT_BLUE
    #define PROMPT_PATH     BRIGHT_CYAN
    #define PROMPT_SYMBOL   BRIGHT_YELLOW
    #define ERROR_COLOR     BRIGHT_RED
    #define SUCCESS_COLOR   BRIGHT_GREEN
    #define WARNING_COLOR   BRIGHT_YELLOW
    #define INFO_COLOR      BRIGHT_CYAN
    #define COMMAND_COLOR   WHITE
    #define SEPARATOR_COLOR BRIGHT_BLACK

    // ---- Function prototypes ----
    void print_colored(const char *color, const char *text);
    void print_success(const char *message);
    void print_error(const char *message);
    void print_warning(const char *message);
    void print_info(const char *message);
    void print_welcome_message(void);
    void display_title_banner(void);
    void display_user_welcome(void);
    void display_command_help(void);
    char *get_current_user(void);
    char *get_hostname(void);
    char *get_home_relative_path(const char *path);
    int check_home_prefix(const char *path, const char *home_path, int home_len);
    char *build_relative_path(const char *path, int home_len, int path_len);

#endif /* COLORS_H */
