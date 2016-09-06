#ifndef ERROR_H
#define ERROR_H

#include <stdarg.h>

void err_quit(const char *fmt, ...);
void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);


#endif // ERROR_H

