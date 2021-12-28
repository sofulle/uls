

#include "uls.h"

void mx_del_liarr(ls_list ***args, ls_list **dirs) {
    ls_list **del_arr = *args;

    for (int i = 0; del_arr[i]!= NULL; i++) {
        mx_strdel(&del_arr[i]->name);
        mx_strdel(&del_arr[i]->path);
        if (del_arr[i]->err)
            mx_strdel(&del_arr[i]->err);
        free(del_arr[i]);
        del_arr[i] = NULL;
    }

    free(*args);
    *args = dirs;
}
