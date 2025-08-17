// ============================
//       BUILTIN_CAT
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

static int cat_check_file_type(char const *path)
{
    struct stat file_stat;
    int result;

    result = stat(path, &file_stat);
    if (result == -1) {
        result = lstat(path, &file_stat);
        if (result == -1) {
            return 0;
        }
    }
    if (S_ISREG(file_stat.st_mode)) {
        return 1;
    }
    if (S_ISDIR(file_stat.st_mode)) {
        return 2;
    }
    return 0;
}

static int cat_handle_file(char const *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == 0) {
        my_printf("cat: %s: File size: ", path);
        my_put_nbr((int)file_stat.st_size);
        my_printf(" bytes\n");
        my_printf("(File content reading not implemented in pongsh)\n");
        return 0;
    }
    my_printf("cat: %s: Cannot access file\n", path);
    return -1;
}

static int cat_handle_directory(char const *path)
{
    my_printf("cat: %s: Is a directory\n", path);
    return -1;
}

int pongsh_cat(char **args)
{
    int file_type;

    if (args[1] == NULL) {
        my_printf("cat: missing operand\n");
        return 1;
    }
    file_type = cat_check_file_type(args[1]);
    if (file_type == 1) {
        cat_handle_file(args[1]);
    } else if (file_type == 2) {
        cat_handle_directory(args[1]);
    } else {
        my_printf("cat: %s: No such file or directory\n", args[1]);
    }
    return 1;
}
