/**
 * ============================================================================
 *                              MY_LS HEADER
 * ============================================================================
 * File: my_ls.h
 * Description: Header file for the my_ls implementation - builtin ls command
 *              for the PONGSH shell.
 * Dependencies: pongsh.h
 * ============================================================================
 */

#ifndef MY_LS_H
    #define MY_LS_H

    #include <dirent.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <time.h>
    #include <pwd.h>
    #include <grp.h>
    #include "pongsh.h"

/* Function prototypes */
int my_ls(const char *path);
int my_ls_with_flags(const char *path, const char *flags);
void parse_ls_flags(const char *flags, int *show_hidden, int *show_details);
DIR *open_directory(const char *dir_path);
void sort_entries(char **entries, int count);
int read_directory_entries(DIR *dir, char **entries, int show_hidden);
void free_entries(char **entries, int count);
void display_entries(char **entries, int count, const char *dir_path,
    int show_details);
void process_directory_entries(DIR *dir, const char *dir_path,
    int show_hidden, int show_details);
void print_file_info(const char *filename, const char *path, int show_details);
void print_detailed_info(const struct stat *file_stat, const char *filename);
void print_permissions(mode_t mode);
void print_file_size(off_t size);
void print_file_time(time_t mtime);

#endif /* MY_LS_H */
