// uls_enums.h
#ifndef ULS_ENUMS_H
#define ULS_ENUMS_H

typedef enum sort_e {
    SORT_DEFAULT,
    SORT_BY_SIZE,
    SORT_BY_TIME_MOD
} sort_t;

typedef enum output_e {
    OUTPUT_MTLCOLUMN,
    OUTPUT_ONECOLUMN,
    OUTPUT_LIST
} output_t;

typedef enum entry_e {
    ENTRY_DEFAULT,
    ENTRY_HIDDEN,
    ENTRY_ALL
} entry_t;

#endif // !ULS_ENUMS_H
