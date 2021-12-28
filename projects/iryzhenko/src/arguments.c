// arguments.c

#include "uls.h"

void arguments_set_flags(app_t *app, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        int len = mx_strlen(argv[i]);

        if(argv[i][0] != '-' || len < 2) break;

        app->keys_count++;
        app->flags_is_changed = true;

        if(!mx_strcmp(argv[i], "--")) break;

        for (int j = 1; j < len; j++) {
            switch (argv[i][j]) {
                case 'A': {
                    if(app->flags.entry != ENTRY_ALL) app->flags.entry = ENTRY_HIDDEN;
                    break;
                }
                case 'C': {
                    app->flags.output = OUTPUT_MTLCOLUMN;
                    break;
                }
                case 'G': {
                    app->flags.colorized_view = true;
                    break;
                }
                case 'R': {
                    app->flags.recursive_search = true;
                    break;
                }
                case 'S': {
                    app->flags.sort = SORT_BY_SIZE;
                    break;
                }
                case 'T': {
                    app->flags.list_full_time = true;
                    break;
                }
                case 'a': {
                    app->flags.entry = ENTRY_ALL;
                    break;
                }
                case 'h': {
                    app->flags.list_size_units = true;
                    break;
                }
                case 'l': {
                    app->flags.output = OUTPUT_LIST;
                    break;
                }
                case 'r': {
                    app->flags.reverse = true;
                    break;
                }
                case 't': {
                    if(app->flags.sort == SORT_DEFAULT) app->flags.sort = SORT_BY_TIME_MOD;
                    break;
                }
                case '1': {
                    app->flags.output = OUTPUT_ONECOLUMN;
                    break;
                }
                
                default: {
                    error_get_usage();
                    break;
                }
            }
        }
    }

    #ifdef _DEBUG_
        debug_print_flags(app);
    #endif
}

void arguments_set_paths(app_t *app, int argc, char **argv) {
    for (int i = app->keys_count + 1; i < argc; i++) {
        directory_t *dir = malloc(sizeof(directory_t));
        dir->name = mx_strdup(argv[i]);
        dir->error = 0;

        if(app->directories == NULL) {
            app->directories = mx_create_node(dir);
        }
        else {
            mx_push_back(&app->directories, dir);
        }
    }

    if(app->directories == NULL) {
        directory_t *dir = malloc(sizeof(directory_t));
        dir->name = ".";
        dir->error = 0;
        mx_push_back(&app->directories, dir);
    }

    #ifdef _DEBUG_
        debug_print_directories(app);
    #endif
}
