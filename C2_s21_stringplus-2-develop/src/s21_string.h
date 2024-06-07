#ifndef S21_STRING
#define S21_STRING
#define s21_size_t unsigned long long
#define s21_NULL (void *)0

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Mem functions

/*Выполняет поиск первого вхождения символа c (беззнаковый тип)
в первых n байтах строки, на которую указывает аргумент str.*/
void *s21_memchr(const void *str, int c, s21_size_t n);

/*Сравнивает первые n байтов str1 и str2.*/
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

/*Копирует n символов из src в dest.*/
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

/*Еще одна функция для копирования n символов из src в dest.*/
void *s21_memmove(void *dest, const void *src, s21_size_t n);

/*Копирует символ c (беззнаковый тип)
в первые n символов строки, на которую указывает аргумент str.*/
void *s21_memset(void *str, int c, s21_size_t n);

// Base string.h functions

/*Добавляет строку, на которую указывает src,
в конец строки, на которую указывает dest.*/
char *s21_strcat(char *dest, const char *src);

/*Добавляет строку, на которую указывает src, в конец строки,
на которую указывает dest, длиной до n символов.*/
char *s21_strncat(char *dest, const char *src, s21_size_t n);

/*Выполняет поиск первого вхождения символа c (беззнаковый тип)
в строке, на которую указывает аргумент str.*/
char *s21_strchr(const char *str, int c);

/*Сравнивает строку, на которую указывает str1,
со строкой, на которую указывает str2.*/
int s21_strcmp(const char *str1, const char *str2);

/*Сравнивает не более первых n байтов str1 и str2.*/
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

/*Копирует строку, на которую указывает src, в dest.*/
char *s21_strcpy(char *dest, const char *src);

/*Копирует до n символов из строки, на которую указывает src, в dest.*/
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

/*Вычисляет длину начального сегмента str1,
который полностью состоит из символов, не входящих в str2.*/
s21_size_t s21_strcspn(const char *str1, const char *str2);

/*Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
 * указатель на строку с сообщением об ошибке. Нужно объявить макросы,
 * содержащие массивы сообщений об ошибке для операционных систем mac и linux.
 * Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
 * осуществляется с помощью директив.*/
char *s21_strerror(int errnum);

/*Вычисляет длину строки str, не включая завершающий нулевой символ.*/
s21_size_t s21_strlen(const char *str);

/*Находит первый символ в строке str1,
который соответствует любому символу, указанному в str2.*/
char *s21_strpbrk(const char *str1, const char *str2);

/*Выполняет поиск последнего вхождения символа c (беззнаковый тип)
в строке, на которую указывает аргумент str.*/
char *s21_strrchr(const char *str, int c);

/*Вычисляет длину начального сегмента str1,
который полностью состоит из символов str2.*/
s21_size_t s21_strspn(const char *str1, const char *str2);

/*Находит первое вхождение всей строки needle
(не включая завершающий нулевой символ), которая появляется в строке haystack.*/
char *s21_strstr(const char *haystack, const char *needle);

/*Разбивает строку str на ряд токенов, разделенных delim.*/
char *s21_strtok(char *str, const char *delim);

/*Возвращает копию строки (str), преобразованной в верхний регистр.*/
void *s21_to_upper(const char *str);
/*Возвращает копию строки (str), преобразованной в нижний регистр.*/
void *s21_to_lower(const char *str);
/*Возвращает новую строку, в которой указанная строка (str) вставлена в
указанную позицию (start_index) в данной строке (src).*/
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
/*Возвращает новую строку, в которой удаляются все начальные и конечные
вхождения набора заданных символов (trim_chars) из данной строки (src).*/
void *s21_trim(const char *src, const char *trim_chars);

// stdio.h functions

/*str − Это С-строка, которую функция обрабатывает в качестве источника для
извлечения данных;

format − это С-строка, содержащая один или несколько следующих элементов:
пробельный символ, непробельный символ и спецификаторы формата. Спецификатор
формата для печатающих функций следует прототипу:
%[флаги][ширина][.точность][длина]спецификатор. Спецификатор формата для
сканирующих функций следует прототипу: %[*][ширина][длина]спецификатор.*/

/*считывает форматированный ввод из строки.*/
int s21_sscanf(const char *str, const char *format, ...);

// Определение структуры format_spec, которая содержит параметры форматирования
typedef struct {
  int minus_flag;  // Флаг выравнивания по левому краю
  int plus_flag;  // Флаг отображения знака "+" для положительных чисел
  int space_flag;  // Флаг отображения пробела для положительных чисел без знака
  int width;       // Ширина поля
  int precision;   // Точность
  int length_modifier;  // Модификатор длины
  char format_specifier;  // Спецификатор формата ('d', 'x', 'f' и т.д.)
  int zero_flag;  // Флаг заполнения нулями
  int sharp_flag;
} format_spec;

/*отправляет форматированный вывод в строку, на которую указывает str.*/
int s21_sprintf(char *str, const char *format, ...);
/*парсим форматы*/
void s21_process_format(const char **format, va_list args, char **p);
/*парсим флаги*/
void s21_parse_flags(const char **format, format_spec *spec);
/*проверяет, является ли символ цифрой*/
int s21_my_isdigit(char c);
/*разбор ширины поля*/
void s21_parse_width(const char **format, format_spec *spec, va_list args);
/*разбор точности*/
void s21_parse_precision(const char **format, format_spec *spec, va_list args);
/*разбор модификатора длины*/
void s21_parse_length_modifier(const char **format, format_spec *spec);
/*исполнение всех специфиакторов формата*/
int s21_parse_format_spec(const char **format, format_spec *spec, va_list args);
/*возвращаем кол-во нулей*/
int s21_get_num_zeros(int precision, int len);
/*возвращаем кол-во пробелов*/
int s21_get_num_spaces(int width, int len, int num_zeros, bool negative);
/*выводит знак чилса*/
void s21_print_sign(char **p, char sign);
/*выводим нули перед числом*/
void s21_print_zeros(char **p, int num_zeros);
/*выводим пробелы после числа*/
void s21_print_space(char **p, int num_spaces, char fill_char);
/*для печати числа*/
char *s21_print_int(va_list args, char *p, format_spec *spec);
/*печатаем заданное кол-во пробелов*/
void s21_print_spaces(int num_spaces, char **p);
/*для печати символа*/
char *s21_print_char(va_list args, char *p, format_spec *spec);
/*получаем строку из аргументов переменной длины, если она не является NULL,
 * иначе возвращаем строку "(null)"*/
const char *s21_get_string(va_list args);
/*получаем длину строки*/
int s21_get_len(const char *s);
/*получаем точность для вывода строки*/
int s21_get_precision(format_spec *spec, int len);
/*получаем ширину поля для вывода строки*/
int s21_get_width(format_spec *spec, int len);
/*выводим заданное количество символов fill_char в выходной буфер*/
void s21_print_fill_chars(char **p, int num_fill, char fill_char);
/*функция для печати строки*/
char *s21_print_str(va_list args, char *p, format_spec *spec);
/*вычисляем значение для округления*/
double s21_compute_rounding(int precision);
/*разбиваем число на целую и дробную части*/
void s21_split_number(long double num, long long *integer_part,
                      long double *fractional_part);
/*конвертируем целую часть числа в строку*/
int s21_convert_integer_to_string(long long integer_part, char *integer_str);
/*конвертируем дробную часть числа в строку*/
int s21_convert_fract_to_string(double fractional_part, int precision,
                                char *fractional_str);
/*добавляем пробелы или нули для выравнивания числа*/
void s21_add_spaces_or_zeros(char **p, int width, int total_len);
/*добавляем знак числа*/
void s21_add_sign(char **p, int sign, format_spec *spec);
/*добавляем целую и дробную части числа в выходной буфер*/
void s21_add_parts(char **p, char *integer_str, int integer_len,
                   char *fractional_str, int fractional_len, int precision);
/*функция для вывода числа с плавающей точкой*/
char *s21_print_float(va_list args, char *p, format_spec *spec);
/*заполняет буфер числом, преобразованным в нужную систему счисления*/
char *s21_buffer_fill(char *q, unsigned long int num, int base,
                      char start_letter);
/*печать число*/
char *s21_print_number(char *p, char *q, int len, format_spec *spec, char flag);
/*получить число*/
unsigned long int s21_get_number(va_list args, format_spec *spec);
/*напечатать число в шестнадцатиричном формате*/
char *s21_print_hex(va_list args, char *p, format_spec *spec);
/*напечатать число в шестнадцатиричном формате с буквами в верхнем регистре*/
char *s21_print_hex_upper(va_list args, char *p, format_spec *spec);
/*напечатать десятичное число*/
char *s21_print_ten(va_list args, char *p, format_spec *spec);
/*добавляет "%" в строку результата*/
char *s21_print_procent(char *p);

char *s21_print_oct(va_list args, char *p, format_spec *spec);
char *s21_print_exp(va_list args, char *p, format_spec *spec,
                    const char *format);
char *s21_print_pointer(va_list args, char *p, format_spec *spec);
/*для проверки корректности основания системы счисления*/
int s21_is_valid_base(int base);
/*для обработки отрицательных чисел и установки флага знака*/
int s21_handle_negative(long int *value);
/*для записи цифрр числа в обратном порядке в строку*/
int s21_write_digits(long int value, char *str, int base);
/*для переворачивания строки*/
void s21_reverse_string(char *str, int len);

/*для преобразования целочисленного значения в строку для "d"*/
char *s21_itoa_d(long int value, char *str, int base);
long double get_double(va_list args, format_spec *spec);
void convert_to_exp(int *exp_precision, long double *num);
void exp_suffix(char *exp_str, int exp_precision, char e_symb);

#ifdef __APPLE__
#define s21_error                                                              \
  {                                                                            \
    "Undefined error: 0", "Operation not permitted",                           \
        "No such file or directory", "No such process",                        \
        "Interrupted system call", "Input/output error",                       \
        "Device not configured", "Argument list too long",                     \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource deadlock avoided", "Cannot allocate memory",                 \
        "Permission denied", "Bad address", "Block device required",           \
        "Resource busy", "File exists", "Cross-device link",                   \
        "Operation not supported by device", "Not a directory",                \
        "Is a directory", "Invalid argument", "Too many open files in system", \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain", "Result too large", \
        "Resource temporarily unavailable", "Operation now in progress",       \
        "Operation already in progress", "Socket operation on non-socket",     \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol family",                     \
        "Address already in use", "Can't assign requested address",            \
        "Network is down", "Network is unreachable",                           \
        "Network dropped connection on reset",                                 \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available", "Socket is already connected",            \
        "Socket is not connected", "Can't send after socket shutdown",         \
        "Too many references: can't splice", "Operation timed out",            \
        "Connection refused", "Too many levels of symbolic links",             \
        "File name too long", "Host is down", "No route to host",              \
        "Directory not empty", "Too many processes", "Too many users",         \
        "Disc quota exceeded", "Stale NFS file handle",                        \
        "Too many levels of remote in path", "RPC struct is bad",              \
        "RPC version wrong", "RPC prog. not avail", "Program version wrong",   \
        "Bad procedure for program", "No locks available",                     \
        "Function not implemented", "Inappropriate file type or format",       \
        "Authentication error", "Need authenticator", "Device power is off",   \
        "Device error", "Value too large to be stored in data type",           \
        "Bad executable (or shared library)", "Bad CPU type in executable",    \
        "Shared library version mismatch", "Malformed Mach-o file",            \
        "Operation canceled", "Identifier removed",                            \
        "No message of desired type", "Illegal byte sequence",                 \
        "Attribute not found", "Bad message", "EMULTIHOP (Reserved)",          \
        "No message available on STREAM", "ENOLINK (Reserved)",                \
        "No STREAM resources", "Not a STREAM", "Protocol error",               \
        "STREAM ioctl timeout", "Operation not supported on socket",           \
        "Policy not found", "State not recoverable", "Previous owner died",    \
        "Interface output queue is full"                                       \
  }
#endif

#ifdef __linux__
#define s21_error                                                              \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "Unknown error 41",               \
        "No message of desired type", "Identifier removed",                    \
        "Channel number out of range", "Level 2 not synchronized",             \
        "Level 3 halted", "Level 3 reset", "Link number out of range",         \
        "Protocol driver not attached", "No CSI structure available",          \
        "Level 2 halted", "Invalid exchange", "Invalid request descriptor",    \
        "Exchange full", "No anode", "Invalid request code", "Invalid slot",   \
        "Unknown error 58", "Bad font file format", "Device not a stream",     \
        "No data available", "Timer expired", "Out of streams resources",      \
        "Machine is not on the network", "Package not installed",              \
        "Object is remote", "Link has been severed", "Advertise error",        \
        "Srmount error", "Communication error on send", "Protocol error",      \
        "Multihop attempted", "RFS specific error", "Bad message",             \
        "Value too large for defined data type", "Name not unique on network", \
        "File descriptor in bad state", "Remote address changed",              \
        "Can not access a needed shared library",                              \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }
#endif

#endif  // STRING_21_H_
