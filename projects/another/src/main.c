#include "uls.h"

static void err_flag(st_fl **fl, char flag) {
    free(*fl);
    fl = NULL;
    mx_printerr("uls: illegal option -- ");
    mx_printcharerr(flag);
    mx_printerr("\n");
    mx_printerr("usage: uls [-ACGRSTcfglmortux1] [file ...]\n");
    exit(-1);
}

static void nulloutput(st_fl **fl) {
    (*fl)->x = 0;
    (*fl)->l = 0;
    (*fl)->C = 0;
    (*fl)->m = 0;
    (*fl)->fr = 0;
}

static void add_flags(st_fl **fl, char flag) {
    if (flag == 'T')
        (*fl)->T = 1;
    else if (flag == 'G' && isatty(1))
        (*fl)->G = 1;
    else if (flag == 'c') {
        (*fl)->u = 0;
        (*fl)->c = 1;
    }
    else if (flag == 't')
        (*fl)->t = 1;
    else if (flag == 'u') {
        (*fl)->u = 1;
        (*fl)->c = 0;
    }

    /* flags_sec */
    else if (flag == 'S')
        (*fl)->S = 1;
    else if (flag == 'r' && (*fl)->r != -1)
        (*fl)->r = 0;
    else if (flag == 'G' && !isatty(1))
        (*fl)->G = 0;
    else if (flag == 'R')
        (*fl)->R = 1;
    else if (flag == 'A')
        (*fl)->A = 1;
	else if (flag == 'g') {
        (*fl)->g = 1;
		(*fl)->l = 1;
	}
    else if (flag == 'o') {
        (*fl)->o = 1;
		(*fl)->l = 1;
	}
    else {
        /* flags_output */
        nulloutput(fl);
        if (flag == 'l')
            (*fl)->l = 1;
        else if (flag == 'C')
            (*fl)->C = 1;
        else if (flag == '1')
            (*fl)->fr = 1;
        else if (flag == 'x')
            (*fl)->x = 1;
        else if (flag == 'm')
            (*fl)->m = 1;
        else
            err_flag(fl, flag);
    }
}

static st_fl *get_flags(char *argv[], int *i) {
    st_fl *fl = malloc(sizeof(st_fl));

    fl->r = 1;
    while(argv[(*i)]) {
        if (argv[(*i)][0] == '-') {
            if (argv[(*i)][1] == '-') {
                (*i)++;
                break;
            }
            if (argv[(*i)][1] == '\0')//если конец строки и нету больше флагов выход
                break;
            for (int j = 1; argv[(*i)][j]; j++) {
                add_flags(&fl, argv[(*i)][j]);//считывает каждый элемент до тех пор пока не считает все флаги указаные  и добавляет их к выполненеию програмы
            }
        }
        else // если нету - то  выход из програмы 
            break;
        (*i)++;
    }
    return fl;
}

int main(int argc, char *argv[]) {
    int count = 1;
    st_fl *fl = get_flags(argv, &count); // добавили все флаги на файл и в структуру и если они есть  далее
    ls_list **args = mx_get_names(argc, argv, count);
    int ex = 0;

    if (args)
        mx_opendir(&args, fl);
    if (fl->ex == 1)
        ex = 1;
    free(fl);
    fl = NULL;

    return ex;
}
