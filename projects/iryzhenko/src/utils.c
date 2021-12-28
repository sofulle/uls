// utils.c

#include "uls.h"

int directory_files_count(char *dir_path, entry_t entry) {
    DIR *dir = opendir(dir_path);
    int ret = 0;

    if(dir == NULL) {
        return -1;
    }

    for(struct dirent *file = readdir(dir); file != NULL; file = readdir(dir)) {
        switch (entry) {
            case ENTRY_DEFAULT: {
                if(file->d_name[0] != '.') ret++;
                break;
            }
            case ENTRY_HIDDEN: {
                if(mx_strcmp(file->d_name, ".") && mx_strcmp(file->d_name, "..")) ret++;
                break;
            }
            case ENTRY_ALL: {
                ret++;
                break;
            }
            default: {
                ret++;
                break;
            }
        }
    }

    closedir(dir);
    return ret;
}

int max_names_length(char **array) {
    int max = 0;
    int temp = 0;

    for (; *array != NULL; array++) {
        temp = mx_strlen(*array);
        if (temp > max) max = temp;
    }

    if (max % 8 == 0) max += 8;
    else max = 8 - (max % 8) + max;

    return max;
}

int win_width() {
    struct winsize win;
    int width = 0;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

    if(isatty(1)) width = win.ws_col;
    else width = 80;

    return width;
}

int array_length(char **files) {
    int ret = 0;

    for (; *files != NULL; files++) {
        ret++;
    }

    return ret;
}

void print_tab(int size) {
    for (int i = 0; i < size; i++) {
        mx_printchar(' ');
    }
}

void print_mode(char *file_path) {
    struct stat st;
    char mode[12];
    acl_t tmp;

    lstat(file_path, &st);

    if (ULS_IS_DIR(st.st_mode))
        mode[0] = 'd';
    else if (ULS_IS_LNK(st.st_mode))
        mode[0] = 'l';
    else if (ULS_IS_BLK(st.st_mode))
        mode[0] = 'b';
    else if (ULS_IS_CHR(st.st_mode))
        mode[0] = 'c';
    else if (ULS_IS_FIFO(st.st_mode))
        mode[0] = 'p';
    else if (ULS_IS_SOCK(st.st_mode))
        mode[0] = 's';
    else if (ULS_IS_WHT(st.st_mode))
        mode[0] = 'w';
    else
        mode[0] = '-';

    mode[1] = (S_IRUSR & st.st_mode) ? 'r' : '-';
    mode[2] = (S_IWUSR & st.st_mode) ? 'w' : '-';
    mode[3] = (S_IXUSR & st.st_mode) ? 'x' : '-';
    mode[4] = (S_IRGRP & st.st_mode) ? 'r' : '-';
    mode[5] = (S_IWGRP & st.st_mode) ? 'w' : '-';
    mode[6] = (S_IXGRP & st.st_mode) ? 'x' : '-';
    mode[7] = (S_IROTH & st.st_mode) ? 'r' : '-';
    mode[8] = (S_IWOTH & st.st_mode) ? 'w' : '-';
    mode[9] = (S_IXOTH & st.st_mode) ? 'x' : '-';

    if (listxattr(file_path, NULL, 0, XATTR_NOFOLLOW) > 0)
        mode[10] = '@';
    else if ((tmp = acl_get_file(file_path, ACL_TYPE_EXTENDED))) {
        acl_free(tmp);
        mode[10] = '+';
    }
    else
        mode[10] = ' ';

    mode[11] = '\0';

    mx_printstr(mode);
}

char *get_full_path(char *dir, char *file) {
    int dir_len = mx_strlen(dir);
    int file_len = mx_strlen(file);
    int fullpath_len = dir_len + file_len + 1;
    char *full_path = malloc(fullpath_len * sizeof(char));

    for (int i = 0; i < dir_len; i++) {
        full_path[i] = dir[i];
    }
    full_path[dir_len] = '/';
    for (int i = 0; i < file_len; i++) {
        full_path[dir_len + i + 1] = file[i];
    }
    full_path[fullpath_len] = '\0';

    return full_path;
}

void print_time(char *file_path) {
    struct stat buff;
    char time_ret[13];
    char *time_temp = NULL;
    time_t time_cur = time(NULL);
    char year_cur[5];
    char year_buf[5];

    time_temp = ctime(&time_cur);
    for (int i = 0; i < 5; i++) {
        year_cur[i] = time_temp[i + 20];
    }
    year_cur[4] = '\0';

    lstat(file_path, &buff);
    time_temp = ctime(&buff.st_mtimespec.tv_sec);
    for (int i = 0; i < 5; i++) {
        year_buf[i] = time_temp[i + 20];
    }
    year_buf[4] = '\0';

    for (int i = 0; i < 7; i++) {
        time_ret[i] = time_temp[i + 4];
    }

    if(mx_strcmp(year_cur, year_buf)) {
        time_ret[7] = ' ';
        for (int i = 0; i < 4; i++) {
            time_ret[i + 8] = time_temp[i + 20];
        }
    }
    else {
        for (int i = 0; i < 5; i++) {
            time_ret[i + 7] = time_temp[i + 11];
        }
    }

    time_ret[12] = '\0';

    mx_printstr(time_ret);
}

void printstr_fll(char *str, int full_size) {
    int offset = full_size - mx_strlen(str);

    for (int i = 0; i < offset; i++) {
        mx_printchar(' ');
    }
    
    mx_printstr(str);
}

void print_symblink(char *file_path) {
    struct stat st;
    char *buf = NULL;
    ssize_t nbytes = 0;
    ssize_t buf_size = 0;

    lstat(file_path, &st);

    if (!ULS_IS_LNK(st.st_mode)) return;

    buf_size = st.st_size == 0 ? 100 : st.st_size + 1;
    buf = mx_strnew(buf_size);
    nbytes = readlink(file_path, buf, buf_size);

    if (nbytes >= 0)
        mx_printstr(buf);
    mx_strdel(&buf);
}
