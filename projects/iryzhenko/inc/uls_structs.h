// uls_structs.h
#ifndef ULS_STRUCTS_H
#define ULS_STRUCTS_H

typedef struct flags_s {
    bool recursive_search;

    bool reverse;

    bool colorized_view;

    // List output args
    bool list_size_units;
    bool list_full_time;

    output_t output;
    entry_t entry;
    sort_t sort;
} flags_t;

typedef struct directory_s {
    char *name;
    char **files;
    int error;
} directory_t;

typedef struct app_s {
    flags_t flags;
    bool flags_is_changed;
    int keys_count;
    t_list *directories;
    t_list *files;
} app_t;

#endif // !ULS_STRUCTS_H
