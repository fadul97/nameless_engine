#ifndef ERROR_LIST_H
#define ERROR_LIST_H

typedef enum
{
    OK,
    ERR_WINDOW,
    ERR_INPUT,
    ERR_GC,
    ERR_RENDERER,
    ERR_OBJ_LOADER,
    ERR_END
} ErrorCode;

extern const char *error_names[ERR_END + 1];

#endif // ERROR_LIST_H