
#include "uls.h"

static ls_list *create_file_node(ls_list *arg) {
    ls_list *node = (ls_list *)malloc(1 * sizeof (ls_list));

    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    node->err = NULL;
    if (arg->err != NULL)
        node->err = mx_strdup(arg->err);
    lstat(node->path, &(node->info));
    if (arg->open != NULL)
        node->open = arg->open;
    else 
        node->open = NULL;
    return node;
}

static void create_fde(ls_list ***dirs, ls_list ***args) {
    int nDir = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->err == NULL)
            if (MX_IS_DIR((*args)[i]->info.st_mode) && 
                mx_strcmp((*args)[i]->name, ".") != 0 &&
                mx_strcmp((*args)[i]->name, "..") != 0)
                nDir++;

    if (nDir > 0)
        *dirs = malloc((nDir + 1) * sizeof(ls_list *));
}

void mx_del_files(ls_list ***args, st_fl *fl) {
   ls_list **dirs = NULL;
    int nDir = 0;

    create_fde(&dirs, args);
    for (int i = 0; (*args)[i] != NULL; i++) {
        if ((*args)[i]->err == NULL) {
            if (MX_IS_DIR((*args)[i]->info.st_mode) && 
                mx_strcmp((*args)[i]->name, ".") != 0 && 
                mx_strcmp((*args)[i]->name, "..") != 0) {
                dirs[nDir++] = create_file_node((*args)[i]);
                dirs[nDir] = NULL;
            }
        }
    }
    fl->fl = 1;
    mx_del_liarr(args, dirs);
}
