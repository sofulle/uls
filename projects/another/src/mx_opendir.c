#include "uls.h"

static int check_a(char *name, st_fl *fl) {
    if (fl->A != 1)
        return 0;
    if (mx_strcmp(name, ".") == 0)
        return 0;
    if (mx_strcmp(name, "..") == 0)
        return 0;
    return 1;
}

static int count_read(ls_list **arg, st_fl *fl) {
    int count = 0;
    ls_list *args = *arg;
    DIR *dptr;
    struct dirent *ds;

    if (MX_IS_DIR(args->info.st_mode) ||  MX_IS_LNK(args->info.st_mode)) {
        if ((dptr = opendir(args->path)) != NULL) {
            while ((ds = readdir(dptr)) != NULL)
                if (ds->d_name[0] != '.' 
                    || check_a(ds->d_name, fl) == 1)
                    count++;
            closedir(dptr);
        }
        else {
            (*arg)->err = mx_strdup(strerror(errno));
            fl->ex = 1;
            return -1;
        }
    }
    return count;
}

static ls_list *create_he_node(char *name, char *path) {
    ls_list *node = (ls_list *)malloc(1 * sizeof(ls_list));

    node->name = mx_strdup(name);
    node->path = mx_strdup(path);
    mx_join(&node->path, "/");
    mx_join(&node->path, name);
    node->err = NULL;

    if (lstat(node->path, &(node->info)) == -1)
        node->err = mx_strdup(strerror(errno));
    node->open = NULL;
    return node;
}

static void open_dir(ls_list ***args, st_fl *fl) {
    DIR *dptr;
    struct dirent *ds;
    int count = 0;

    for (int i = 0; (*args)[i] != NULL; i++) {
        count = count_read(&(*args)[i], fl);
        if (count > 0) {
            (*args)[i]->open = malloc((count + 1) * sizeof(ls_list *));
            if ((dptr = opendir((*args)[i]->path)) != NULL) {
                for (count = 0; (ds = readdir(dptr)) != NULL;)
                    if (ds->d_name[0] != '.' 
                        || check_a(ds->d_name, fl) == 1)
                        (*args)[i]->open[count++] = 
                        create_he_node(ds->d_name, (*args)[i]->path);
                (*args)[i]->open[count] = NULL;
            closedir(dptr);
            }
        }
    }
    mx_out_put_all(args, fl);
}

void mx_opendir(ls_list ***args, st_fl *fl) {
    ls_list **files = mx_get_files(&(*args), fl);

	if (files) {
		mx_out_put_menu(&files, fl, 0);
		if (*args)
			mx_printchar('\n');
		fl->fl = 1;
        mx_del_arr_arr(&files);
	}
    if (*args)
        open_dir(&(*args), fl);
}
