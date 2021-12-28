// uls_error.h
#ifndef ULS_ERROR_H
#define ULS_ERROR_H

/// Enumeration that contains all error types.
typedef enum e_error {
    ERROR_INVALID_ARGS,
    ERROR_FILE_NOT_EXIST,
    ERROR_EMPTY_FILE,
    ERROR_INVALID_LINE,
    ERROR_INVALID_VERTICES_NUMBER,
    ERROR_DUPLICATE_PATHS,
    ERROR_OUT_OF_INT_MAX,
    ERROR_MEMORY_ALLOC,
    ERROR_SEG_FAULT
} t_error;

/// A function that stops application and throws error message to the standard error output.
/// \param str string argument
void error_throw(int err, char *str);

void error_get_usage();

#endif // !ULS_ERROR_H
