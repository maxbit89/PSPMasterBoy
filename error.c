/*
    error.c --
    Error logging routines
*/

#include "shared.h"

#ifdef DEBUG
static FILE *error_log;
#endif

struct {
    int enabled;
    int verbose;
    FILE *log;
} t_error;

void error_init(void)
{
#ifdef DEBUG
    error_log = fopen("error.log","w");
#endif
}

void error_shutdown(void)
{
#ifdef DEBUG
    if(error_log) fclose(error_log);
#endif
}

void error(char *format, ...)
{
#ifdef DEBUG
    va_list ap;
    va_start(ap, format);
    if(error_log) vfprintf(error_log, format, ap);
    va_end(ap);
#endif
}

void dbg(char *format, ...)
{
    char buffer[4096];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buffer, 4096, format, ap);
    sceIoWrite(sceKernelStdout(), buffer, 4096);
    va_end(ap);
}

void trap(char *file, int line)
{
    dbg("TRAP: %s:%d", file, line);
}

