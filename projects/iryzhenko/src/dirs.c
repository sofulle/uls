// dirs.c

#include "uls.h"

void dirs_sort(app_t *app) {
    app->keys_count = app->keys_count;
    mx_sort_list(app->directories, dirs_cmp);
}

bool dirs_cmp(void *dir_a, void *dir_b) {
    char *name_a = ((directory_t *)dir_a)->name;
    char *name_b = ((directory_t *)dir_b)->name;

    if(mx_strcmp(name_a, name_b) > 0) return true;
    else return false;
}
