// uls_error.h
#ifndef ULS_DEFINITIONS_H
#define ULS_DEFINITIONS_H

#define FLAGS_LIST "ACal1" //"ACGRSTahlrt1"

#define ULS_IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define ULS_IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define ULS_IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define ULS_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define ULS_IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define ULS_IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define ULS_IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define ULS_IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)
#define ULS_IS_EXEC(mode) ((mode) & S_IXUSR)

#endif // !ULS_DEFINITIONS_H
