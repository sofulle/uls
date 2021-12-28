// files.c

#include "uls.h"

void files_find(app_t *app) {
    for (t_list *node = app->directories; node != NULL; node = node->next) {
        directory_t *dir = (directory_t *)node->data;
        char **paths = NULL;
        int files_count = 0;
        int offset = 0;
        DIR *_dir = opendir(dir->name);

        if(_dir == NULL) {
            dir->error = errno;
            errno = 0;
            dir->files = NULL;
            continue;
        }

        files_count = directory_files_count(dir->name, app->flags.entry);
        offset = directory_files_count(dir->name, ENTRY_ALL) - files_count;
        paths = malloc((files_count + 1) * sizeof(char *));

        for (int i = 0; i < offset; i++) {
            readdir(_dir);
        }
        for (int i = 0; i < files_count; i++) {
            char *file = readdir(_dir)->d_name;
            paths[i] = mx_strdup(file);
        }
        paths[files_count] = NULL;

        dir->files = paths;

        closedir(_dir);
    }
}

void files_sort(app_t *app) {
    for (t_list *node = app->directories; node != NULL; node = node->next) {
        directory_t *dir = (directory_t *)node->data;

        if(dir->files == NULL) continue;

        int size = 0;
        for (char **file = dir->files; *file != NULL; file++) {
            size++;
        }

        mx_bubble_sort(dir->files, size);
    }
}
