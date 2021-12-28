// uls_functions.h
#ifndef ULS_FUNCTIONS_H
#define ULS_FUNCTIONS_H

#include "uls.h"

app_t *app_init();
void app_exit(app_t *app);

void arguments_set_flags(app_t *app, int argc, char **argv);
void arguments_set_paths(app_t *app, int argc, char **argv);

void dirs_sort(app_t *app);
bool dirs_cmp(void *dir_a, void *dir_b);

void files_find(app_t *app);
void files_sort(app_t *app);

void output_print(app_t *app);
void output_print_mcol(directory_t *dir);
void output_print_ocol(directory_t *dir);
void output_print_list(directory_t *dir);

int directory_files_count(char *dir_path, entry_t entry);
int max_names_length(char **array);
int win_width();
int array_length(char **files);
void print_tab(int size);
void print_mode(char *file_path);
char *get_full_path(char *dir, char *file);
void print_time(char *file_path);
void printstr_fll(char *str, int full_size);
void print_symblink(char *file_path);

#endif // !ULS_FUNCTIONS_H
