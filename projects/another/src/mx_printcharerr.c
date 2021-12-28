#include "uls.h"

void mx_out_err(ls_list ***error, st_fl *fl) {
    if (error && *error && **error) {
        mx_sort(error, fl);
        fl->fl = 1;
        fl->ex = 1;
        for (int i = 0; (*error)[i]; i++) {
            mx_printerr("uls: ");
            mx_printerr((*error)[i]->name);
            mx_printerr(": ");
            mx_printerr((*error)[i]->err);
            mx_printerr("\n");
            mx_strdel(&(*error)[i]->name);
            mx_strdel(&(*error)[i]->path);
            mx_strdel(&(*error)[i]->err);
            free((*error)[i]);
            (*error)[i] = NULL;
        }

        free(*error);
        *error = NULL;
    }
}

void mx_printcharerr(char c) {
    write(2,&c,1);
}
