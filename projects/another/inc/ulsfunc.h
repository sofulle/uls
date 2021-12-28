#include "uls.h"

//small help functions;
void mx_join(char **res, char *s2);
void mx_printstr_g(ls_list *args);
int max_len_names(ls_list **names);
void mx_print_tab(int len, int maxlen);
void mx_del_arr_arr(ls_list ***args);
void mx_printcharerr(char c);
void mx_nulloutput(st_fl **fl);
void mx_err_flag(st_fl **fl, char flag);
int mx_max_len_n_g(ls_list **names);
void mx_print_spaces_g(int len, int maxlen);

//main program;
ls_list **mx_get_names(int argc, char **argv, int i);
void mx_opendir(ls_list ***names, st_fl *fl);
void mx_out_put_all(ls_list ***args, st_fl *fl);
void mx_sort(ls_list ***disp, st_fl *fl);
ls_list **mx_get_files(ls_list ***args, st_fl *fl);
void mx_del_files(ls_list ***args, st_fl *fl);
void mx_del_liarr(ls_list ***args, ls_list **dirs);

//outputs:
void mx_out_put_menu(ls_list ***names, st_fl *fl, int flag);
void mx_out_err(ls_list ***error, st_fl *fl);
void mx_output_x(ls_list **names);
void mx_output_c(ls_list **names);
void mx_output_m(ls_list **names, st_fl *fl);
void mx_output_g(ls_list **names, st_fl *fl);
void mx_long_out(ls_list **names, st_fl *fl, int flag);


// flag l
char *mx_get_minor(ls_list *print);
char *mx_get_major(ls_list *print);
bool mx_check_device(ls_list **names, ls_size *size);
char mx_get_file_acl(ls_list *print);
// print func
void mx_print_per(ls_list *print);
char mx_check_per(ls_list *print);
void mx_get_user_name(ls_list *print, int usr);
void mx_get_group_name(ls_list *print, int group);
void mx_edit_time(ls_list *print, char *t, st_fl *fl);
void mx_print_lnk(ls_list *print, ls_size *size);
void mx_print_sz(ls_list *print, ls_size *size);
void mx_print_symblink(ls_list *print);
void mx_print_total(ls_list *total, int blk_size);
void mx_print_all(ls_list *print, ls_size *size, st_fl *fl);
