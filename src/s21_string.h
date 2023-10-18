#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>

#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#define s21_NULL    (void*)0
#define s21_size_t  long unsigned int
#define MAXDIGLEN 128

void*       s21_memchr(const void* str, int c, s21_size_t n);
int         s21_memcmp(const void* str1, const void* str2, s21_size_t n);
void*       s21_memcpy(void* dest, const void* src, s21_size_t n);
void*       s21_memmove(void* dest, const void* src, s21_size_t n);
void*       s21_memset(void* str, int c, s21_size_t n);
char*       s21_strcat(char* destptr, const char* srcptr);
char*       s21_strncat(char* dest, const char* src, s21_size_t n);
char*       s21_strchr(const char* str, int ch);
int         s21_strcmp(const char* str1, const char* str2);
int         s21_strncmp(const char* str1, const char* str2, s21_size_t n);
char*       s21_strcpy(char* destptr, const char* srcptr);
char*       s21_strncpy(char* dest, const char* src, s21_size_t n);
s21_size_t  s21_strcspn(const char* str, const char* sym);
char*       s21_strerror(int num);
s21_size_t  s21_strlen(const char* str);
char*       s21_strpbrk(const char* str, const char* sym);
char*       s21_strrchr(const char* str, int c);
s21_size_t  s21_strspn(const char* str, const char* sym);
char*       s21_strstr(const char* str1, const char* str2);
char*       s21_strtok(char *str, const char *sep);

void*       s21_to_upper(const char* str);
void*       s21_to_lower(const char* str);
void*       s21_insert(const char* src, const char* str, s21_size_t start_index);
void*       s21_trim(const char* src, const char* trim_chars);

int         s21_sscanf(const char * str, const char * format, ...);
int         s21_sprintf(char *str, const char *format, ...);

struct flags {
    int isLONG;
    int isLONGDBL;
    int isSHORT;
    int isSUPPRESS;
    int isSKIP;
    int isPOINT;
    int isLL;  // LONGLONG
    int isSS;  // SHORTSHORT
    int isUnsigned;
    int isSIGN;
    int isDEC;
    int isEXP;
    int isHEX;
    int isPERC;  // %
    int isERR;
    int isALLERR;
};

struct params {
    int inr;
    const char *str;
    const char *fmt;
    s21_size_t width;
    int nassigned;
    int nconversions;
    int nread;
    int base;
    char buf[MAXDIGLEN];
};

int collectCHAR(struct flags *f, struct params *par, va_list input);
void collectSTR(struct flags *f, struct params *par, va_list input);
int collectINT(struct flags *f, struct params *par, va_list input);
int collectFLOAT(struct flags *f, struct params *par, va_list input);

#   if defined(__APPLE__)
#   define ERR_AMOUNT 107
#   define ERRORMSG "Unknown error: %d"
#   define ERROR_LIST {\
        "Undefined error: 0", \
        "Operation not permitted", \
        "No such file or directory", \
        "No such process", \
        "Interrupted system call", \
        "Input/output error", \
        "Device not configured", \
        "Argument list too long", \
        "Exec format error", \
        "Bad file descriptor", \
        "No child processes", \
        "Resource deadlock avoided", \
        "Cannot allocate memory", \
        "Permission denied", \
        "Bad address", \
        "Block device required", \
        "Resource busy", \
        "File exists", \
        "Cross-device link", \
        "Operation not supported by device", \
        "Not a directory", \
        "Is a directory", \
        "Invalid argument", \
        "Too many open files in system", \
        "Too many open files", \
        "Inappropriate ioctl for device", \
        "Text file busy", \
        "File too large", \
        "No space left on device", \
        "Illegal seek", \
        "Read-only file system", \
        "Too many links", \
        "Broken pipe", \
        "Numerical argument out of domain", \
        "Result too large", \
        "Resource temporarily unavailable", \
        "Operation now in progress", \
        "Operation already in progress", \
        "Socket operation on non-socket", \
        "Destination address required", \
        "Message too long", \
        "Protocol wrong type for socket", \
        "Protocol not available", \
        "Protocol not supported", \
        "Socket type not supported", \
        "Operation not supported", \
        "Protocol family not supported", \
        "Address family not supported by protocol family", \
        "Address already in use", \
        "Can't assign requested address", \
        "Network is down", \
        "Network is unreachable", \
        "Network dropped connection on reset", \
        "Software caused connection abort", \
        "Connection reset by peer", \
        "No buffer space available", \
        "Socket is already connected", \
        "Socket is not connected", \
        "Can't send after socket shutdown", \
        "Too many references: can't splice", \
        "Operation timed out", \
        "Connection refused", \
        "Too many levels of symbolic links", \
        "File name too long", \
        "Host is down", \
        "No route to host", \
        "Directory not empty", \
        "Too many processes", \
        "Too many users", \
        "Disc quota exceeded", \
        "Stale NFS file handle", \
        "Too many levels of remote in path", \
        "RPC struct is bad", \
        "RPC version wrong", \
        "RPC prog. not avail", \
        "Program version wrong", \
        "Bad procedure for program", \
        "No locks available", \
        "Function not implemented", \
        "Inappropriate file type or format", \
        "Authentication error", \
        "Need authenticator", \
        "Device power is off", \
        "Device error", \
        "Value too large to be stored in data type", \
        "Bad executable (or shared library)", \
        "Bad CPU type in executable", \
        "Shared library version mismatch", \
        "Malformed Mach-o file", \
        "Operation canceled", \
        "Identifier removed", \
        "No message of desired type", \
        "Illegal byte sequence", \
        "Attribute not found", \
        "Bad message", \
        "EMULTIHOP (Reserved)", \
        "No message available on STREAM", \
        "ENOLINK (Reserved)", \
        "No STREAM resources", \
        "Not a STREAM", \
        "Protocol error", \
        "STREAM ioctl timeout", \
        "Operation not supported on socket", \
        "Policy not found", \
        "State not recoverable", \
        "Previous owner died", \
        "Interface output queue is full"\
    }
#   elif defined(__linux) || defined(__linux__)
#   define ERR_AMOUNT 132
#   define ERRORMSG "No error information"
#   define ERROR_LIST {\
       "No error information", \
       "Operation not permitted", \
"No such file or directory", \
"No such process", \
"Interrupted system call", \
"I/O error", \
"No such device or address", \
"Argument list too long", \
"Exec format error", \
"Bad file descriptor", \
"No child process", \
"Resource temporarily unavailable", \
"Out of memory", \
"Permission denied", \
"Bad address", \
"Block device required", \
"Resource busy", \
"File exists", \
"Cross-device link", \
"No such device", \
"Not a directory", \
"Is a directory", \
"Invalid argument", \
"Too many open files in system", \
"No file descriptors available", \
"Not a tty", \
"Text file busy", \
"File too large", \
"No space left on device", \
"Invalid seek", \
"Read-only file system", \
"Too many links", \
"Broken pipe", \
"Domain error", \
"Result not representable", \
"Resource deadlock would occur", \
"Filename too long", \
"No locks available", \
"Function not implemented", \
"Directory not empty", \
"Symbolic link loop", \
"No error information", \
"No message of desired type", \
"Identifier removed", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Device not a stream", \
"No data available", \
"Device timeout", \
"Out of streams resources", \
"No error information", \
"No error information", \
"No error information", \
"Link has been severed", \
"No error information", \
"No error information", \
"No error information", \
"Protocol error", \
"Multihop attempted", \
"No error information", \
"Bad message", \
"Value too large for data type", \
"No error information", \
"File descriptor in bad state", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Illegal byte sequence", \
"No error information", \
"No error information", \
"No error information", \
"Not a socket", \
"Destination address required", \
"Message too large", \
"Protocol wrong type for socket", \
"Protocol not available", \
"Protocol not supported", \
"Socket type not supported", \
"Not supported", \
"Protocol family not supported", \
"Address family not supported by protocol", \
"Address in use", \
"Address not available", \
"Network is down", \
"Network unreachable", \
"Connection reset by network", \
"Connection aborted", \
"Connection reset by peer", \
"No buffer space available", \
"Socket is connected", \
"Socket not connected", \
"Cannot send after socket shutdown", \
"No error information", \
"Operation timed out", \
"Connection refused", \
"Host is down", \
"Host is unreachable", \
"Operation already in progress", \
"Operation in progress", \
"Stale file handle", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Remote I/O error", \
"Quota exceeded", \
"No medium found", \
"Wrong medium type", \
"Operation canceled", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Previous owner died", \
"State not recoverable" \
    }
#   endif

#endif  // SRC_S21_STRING_H_
