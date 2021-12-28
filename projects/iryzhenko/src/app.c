// app.c

#include "uls.h"

app_t *app_init() {
    app_t *app = malloc(sizeof(app_t));

    app->directories = NULL;
    app->files = NULL;

    if(isatty(STDOUT_FILENO)) app->flags.output = OUTPUT_MTLCOLUMN;
    else app->flags.output = OUTPUT_ONECOLUMN;


    app->flags.entry = ENTRY_DEFAULT;
    app->flags.sort = SORT_DEFAULT;
    app->flags.colorized_view = false;
    app->flags.list_full_time = false;
    app->flags.list_size_units = false;
    app->flags.recursive_search = false;
    app->flags.reverse = false;

    app->flags_is_changed = false;
    app->keys_count = 0;

    return app;
}
void app_exit(app_t *app) {
    free(app);
}
