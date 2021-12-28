#include "uls.h"

static ls_list *create_li_node(char *data) {
    ls_list *node = (ls_list *)malloc(1 * sizeof(ls_list));
//выделяет память исходя из размера списка tli
    node->name = mx_strdup(data);
    //дублирует data   в name в структуру ls_list
    node->path = mx_strdup(data);
    //дублирует data   в path в структуру ls_list
    node->err = NULL;
    if (lstat(data, &(node->info)) == -1)// но в случае символьных сылок она возвращает информацию о самой ссылке, а не о файле, на который она указывает..
        node->err = mx_strdup(strerror(errno));	
        //если ссылки не существует то ощибка
    node->open = NULL;
    return node;
}

static ls_list **create_list(char **name, int count) {
    ls_list **new = malloc(count * sizeof(ls_list *));
    int i = 0;

    for (i = 0; name[i]; i++)
        new[i] = create_li_node(name[i]);
    new[i] = NULL;
    return new;
}

static char **names(int argc, char **argv, int i, int *count) {
    int j = i;
    char **names = NULL;

    if (i == argc) {
        *count = 2;
        names = malloc(2 * sizeof(char *));
        names[0] = mx_strdup(".");
        names[1] = NULL;
    }
    else {
        j = argc;
        names = malloc((j - i + 1) * sizeof(char *));
        for(j = 0; argv[i]; i++, j++)
            names[j] = mx_strdup(argv[i]);
        names[j] = NULL;
        *count = j + 1;
    }
    return names;
}

ls_list **mx_get_names(int argc, char **argv, int i) {
    int count = 0;
    char **name = names(argc, argv, i, &count); //записывает в неймс название файла или папки
    ls_list **args = create_list(name, count);

    mx_del_strarr(&name);
    return args;
}
