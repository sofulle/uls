#include "uls.h"

static ls_list *create_file_node(ls_list *arg) {
    ls_list *node = (ls_list *)malloc(1 * sizeof (ls_list));

    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    if (arg->err)
        node->err = mx_strdup(arg->err);
    else
        node->err = NULL;
    lstat(node->path, &(node->info));
    if (arg->open != NULL)
        node->open = arg->open;
    else
        node->open = NULL;
    return node;
}

static void create_fde(ls_list ***files, ls_list ***dirs, 
                        ls_list ***errors, ls_list ***args) {
    int j = 0;
    int nDir = 0;
    int nErr = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->err == NULL) {
            if (!MX_IS_DIR((*args)[i]->info.st_mode) )
                j++;
            else
                nDir++;
        }
        else
            nErr++;
    if (j > 0)
        *files = malloc((j + 1) * sizeof(ls_list *));
    if (nDir > 0)
        *dirs = malloc((nDir + 1) * sizeof(ls_list *));
    if (nErr > 0)
        *errors = malloc((nErr + 1) * sizeof(ls_list *));
}

static ls_types *create_num() {
    ls_types *num = malloc(sizeof (ls_types));

    num->n_d = 0;
    num->n_e = 0;
    num->n_f = 0;
    num->i = 0;
    return num;
}

static void fdir(ls_list **args, ls_types *num, ls_list ***files, ls_list ***dirs) {
    if (!MX_IS_DIR((*args)->info.st_mode)) {
        (*files)[num->n_f++] = create_file_node((*args));
        (*files)[num->n_f] = NULL;
    }
    else {
        (*dirs)[num->n_d++] = create_file_node((*args));
        (*dirs)[num->n_d] = NULL;
    }
}

ls_list **mx_get_files(ls_list ***args, st_fl *fl) {
    ls_list **files = NULL;
    ls_list **dirs = NULL;
    ls_list **errors = NULL;
    ls_types *num = create_num();

    create_fde(&files, &dirs, &errors, args);
    while ((*args)[num->i] != NULL) {
        if ((*args)[num->i]->err == NULL)
            fdir(&(*args)[num->i], num, &files, &dirs);
        else {
            errors[num->n_e++] = create_file_node((*args)[num->i]);
            errors[num->n_e] = NULL;
        }
        num->i++;
    }

    if (num->n_d > 1)
        fl->fl = 1;
    mx_del_liarr(args, dirs);
    mx_out_err(&errors, fl);
    free(num);
    return files;
}
