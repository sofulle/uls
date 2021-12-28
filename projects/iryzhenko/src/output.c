// output.c

#include "uls.h"

void output_print(app_t *app) {
    bool is_start = true;

    for (t_list *node = app->directories; node != NULL; node = node->next) {
        directory_t *dir = (directory_t *)node->data;

        if(dir->error == ENOENT) {
            error_throw(dir->error, dir->name);
            continue;
        }
    }
    
    for (t_list *node = app->directories; node != NULL; node = node->next) {
        directory_t *dir = (directory_t *)node->data;

        if(dir->error == ENOENT) {
            continue;
        }

        if(is_start) is_start = false;
        else mx_printchar('\n');

        if(1 < mx_list_size(app->directories)) {
            mx_printstr(dir->name);
            mx_printstr(":\n");
        }

        if(dir->error > 0 && dir->error != ENOENT) {
            error_throw(dir->error, dir->name);
            continue;
        }

        switch (app->flags.output) {
            case OUTPUT_MTLCOLUMN:
                output_print_mcol(dir);
                break;

            case OUTPUT_ONECOLUMN:
                output_print_ocol(dir);
                break;

            case OUTPUT_LIST:
                output_print_list(dir);
                break;
            
            default:
                break;
        }
    }
}

void output_print_mcol(directory_t *dir) {
    int namelen = max_names_length(dir->files);
    int arrlen = array_length(dir->files);
    int winwidth = 0;
    int cols = 0;
    int rows = 0;

    if(isatty(STDOUT_FILENO)) winwidth = win_width();
    else winwidth = 80;

    cols = winwidth / namelen;
    rows = arrlen % cols == 0 ? arrlen / cols : arrlen / cols + 1;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if((col * rows) + row >= arrlen) continue;
            mx_printstr(dir->files[(col * rows) + row]);
            print_tab(namelen - mx_strlen(dir->files[(col * rows) + row]));
        }
        mx_printchar('\n');
    }
}

void output_print_ocol(directory_t *dir) {
    for (char **files = dir->files; *files != NULL; files++) {
        mx_printstr(*files);
        mx_printchar('\n');
    }
}

void output_print_list(directory_t *dir) {
    int links_maxlen = 0;
    int username_maxlen = 0;
    int groupid_maxlen = 0;
    int size_maxlen = 0;
    int total = 0;
    bool is_empty = true;

    for (char **file = dir->files; *file != NULL; file++) {
        is_empty = false;
        char *full_path = get_full_path(dir->name, *file);
        struct stat buff;
        lstat(full_path, &buff);

        char *links = mx_itoa(buff.st_nlink);
        char *username = getpwuid(buff.st_uid)->pw_name;
        char *groupid = NULL;
        char *size = mx_itoa(buff.st_size);

        if(getgrgid(buff.st_gid) == NULL)
            groupid = mx_itoa(buff.st_gid);
        else 
            groupid = getgrgid(buff.st_gid)->gr_name;

        total += buff.st_blocks;

        if(mx_strlen(links) > links_maxlen) links_maxlen = mx_strlen(links);
        if(mx_strlen(username) > username_maxlen) username_maxlen = mx_strlen(username);
        if(mx_strlen(groupid) > groupid_maxlen) groupid_maxlen = mx_strlen(groupid);
        if(mx_strlen(size) > size_maxlen) size_maxlen = mx_strlen(size);

        free(full_path);
        free(links);
        free(size);
        if(getgrgid(buff.st_gid) == NULL) free(groupid);

        full_path = NULL;
    }

    if(!is_empty) {
        mx_printstr("total ");
        mx_printint(total);
        mx_printchar('\n');
    }

    for (char **file = dir->files; *file != NULL; file++) {
        char *full_path = get_full_path(dir->name, *file);
        struct stat buff;
        lstat(full_path, &buff);

        char *links = mx_itoa(buff.st_nlink);
        char *username = getpwuid(buff.st_uid)->pw_name;
        char *groupid = NULL;
        char *size = mx_itoa(buff.st_size);

        if(getgrgid(buff.st_gid) == NULL)
            groupid = mx_itoa(buff.st_gid);
        else 
            groupid = getgrgid(buff.st_gid)->gr_name;
        
        print_mode(full_path);
        mx_printstr(" ");
        printstr_fll(links, links_maxlen);
        mx_printstr(" ");
        printstr_fll(username, username_maxlen);
        mx_printstr("  ");
        printstr_fll(groupid, groupid_maxlen);
        mx_printstr("  ");
        printstr_fll(size, size_maxlen);
        mx_printstr(" ");
        print_time(full_path);
        mx_printstr(" ");
        mx_printstr(*file);
        if (ULS_IS_LNK(buff.st_mode)) mx_printstr(" -> ");
        print_symblink(full_path);
        mx_printchar('\n');

        free(full_path);
        free(links);
        free(size);
        if(getgrgid(buff.st_gid) == NULL) free(groupid);

        full_path = NULL;
    }
}
