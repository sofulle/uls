// uls.h
#ifndef ULS_H
#define ULS_H


// === Uncomment to switch to Debug mode
//#define _DEBUG_
// ===


// Include headers from standart libraries
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <unistd.h>
#include <grp.h>

// Include local headers
#include "libmx.h"
#include "uls_definitions.h"
#include "uls_enums.h"
#include "uls_structs.h"
#include "uls_error.h"
#include "uls_functions.h"

#endif // !ULS_H
