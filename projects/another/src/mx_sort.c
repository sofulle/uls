#include "uls.h"

static int ls_cmp_sort_2(ls_list *first, ls_list *second, st_fl *fl) {
    if (fl->c == 1 && fl->t == 1 && fl->S != 1) {
        if (first->info.st_ctime == second->info.st_ctime) {
            if (first->info.st_ctimespec.tv_nsec == second->info.st_ctimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_ctimespec.tv_nsec < second->info.st_ctimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_ctime < second->info.st_ctime) ? 1 : 0;
    }
    else if (fl->t != 1 && fl->S != 1)
        if (mx_strcmp(first->name, second->name) > 0)
            return 1;
    return 0;
}

static int ls_cmp_sort_1(ls_list *first, ls_list *second, st_fl *fl) {
    if (fl->u == 1 && fl->t == 1 && fl->S != 1) {
        if (first->info.st_atime == second->info.st_atime) {
            if (first->info.st_atimespec.tv_nsec == second->info.st_atimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_atimespec.tv_nsec < second->info.st_atimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_atime < second->info.st_atime) ? 1 : 0;
    }
    else 
        return ls_cmp_sort_2(first, second, fl);
}

static int ls_cmp_sort(ls_list *first, ls_list *second, st_fl *fl) {
    if (fl->S == 1) {
        if (first->info.st_size < second->info.st_size)
            return 1;
        if (first->info.st_size == second->info.st_size)
            return mx_strcmp(first->name, second->name);
    }
    else if (fl->t == 1 && fl->c != 1 && fl->u != 1) {
        if (first->info.st_mtime == second->info.st_mtime) {
            if (first->info.st_mtimespec.tv_nsec == second->info.st_mtimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_mtimespec.tv_nsec < second->info.st_mtimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
    }
    return ls_cmp_sort_1(first, second, fl);
}


static int ls_count_size_arr(ls_list **disp) {
	int i = 0;

	while(disp[i])
		i++;
	return i;
}

static void ls_swap_list(ls_list **bondOne, ls_list **bondTwo) {
    ls_list *temp = *bondOne;
    *bondOne = *bondTwo;
    *bondTwo = temp;
}

void mx_sort(ls_list ***disp, st_fl *fl) {
	ls_list **bond = *disp;
	int size = ls_count_size_arr(bond);

	for (int i = 0; i < size; i++) {
		for (int k = i + 1; k < size; k++) {
            if (bond[i]->err != NULL) {
                if (mx_strcmp(bond[i]->name, bond[k]->name) == 1)
                    ls_swap_list(&(bond[i]), &(bond[k]));
            }
            else if (ls_cmp_sort(bond[i], bond[k], fl) == fl->r) {
                ls_swap_list(&(bond[i]), &(bond[k]));
			}
		}
	}
}
