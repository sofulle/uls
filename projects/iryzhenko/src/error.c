// error.c

#include "uls.h"

void error_get_usage() {
    mx_printerr("uls: illegal option -- ");
    write(STDERR_FILENO, &argv[i][j], 1);
    mx_printerr("\n");
    mx_printerr("usage: uls [-");
    mx_printerr(FLAGS_LIST);
    mx_printerr("] [file ...]\n");
    exit(1);
}

void error_throw(int err, char *str) {
    mx_printerr("uls: ");
    mx_printerr(str);
    mx_printerr(": ");
    mx_printerr(strerror(err));
    mx_printerr("\n");
}
