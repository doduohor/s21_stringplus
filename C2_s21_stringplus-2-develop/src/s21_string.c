#include "s21_string.h"

#define BUFF_SIZE 128

#if defined(__APPLE__) || defined(__MACH__)
#define S21_ERRLIST_SIZE 107
#elif defined(__linux__)
#define S21_ERRLIST_SIZE 134
#else
#define S21_ERRLIST_SIZE 134
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)
      str;  // Конвертируем указатель на void в указатель на const unsigned char
  unsigned char ch = (unsigned char)c;  // Приводим символ к типу unsigned char
  int flag = 0;
  void *result = s21_NULL;  // Указатель на результат поиска, изначально
                            // устанавливаем его как NULL

  for (s21_size_t i = 0; i < n && !flag; i++, ptr++) {
    if (*ptr == ch) {
      result = (void *)
          ptr;  // Найдено совпадение, сохраняем указатель на найденный символ
      flag = 1;  // Прерываем цикл, так как уже найден искомый символ
    }
  }

  return result;  // Возвращаем найденный указатель или NULL, если символ не был
                  // найден
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *byte_ptr1 = (const unsigned char *)str1;
  const unsigned char *byte_ptr2 = (const unsigned char *)str2;
  int result = 0;

  for (s21_size_t i = 0; i < n && result == 0; i++) {
    if (byte_ptr1[i] < byte_ptr2[i]) {
      result = -1;
    } else if (byte_ptr1[i] > byte_ptr2[i]) {
      result = 1;
    }
  }

  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d =
      dest;  // Конвертируем указатель на void в указатель на unsigned char
  const unsigned char *s =
      src;  // Конвертируем указатель на void в указатель на const unsigned char

  for (s21_size_t i = 0; i < n; i++) {
    *d++ = *s++;  // Копируем текущий байт из src в dest и инкрементируем
                  // указатели на следующий байт
  }

  return dest;  // Возвращаем указатель на dest
}

void *s21_memmove(void *first_string, const void *second_string,
                  s21_size_t valume) {
  char *destination = (char *)first_string;
  const char *source = (const char *)second_string;
  static char temp[1000] = {'\0'};
  int i = 0;
  int q = valume;
  while ((q--) && (source + i)) {
    temp[i] = source[i];
    i++;
  }
  i = 0;
  q = valume;
  while ((q--) && (destination + i)) {
    destination[i] = temp[i];
    i++;
  }
  return destination;
}
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr =
      str;  // Конвертируем указатель на void в указатель на unsigned char
  unsigned char ch =
      (unsigned char)c;  // Конвертируем значение c в unsigned char

  for (s21_size_t i = 0; i < n; i++) {
    *ptr++ = ch;  // Устанавливаем текущий байт в области памяти равным c и
                  // инкрементируем указатель на следующий байт
  }

  return str;  // Возвращаем указатель на str
}

char *s21_strcat(char *dest, const char *src) {
  if (src != s21_NULL) {
    int i = 0, j = 0;
    for (i = 0; dest[i] != '\0'; i++)
      ;
    for (j = 0; src[j] != '\0'; j++) {
      dest[i + j] = src[j];
    }
    dest[i + j] = '\0';
  }
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  // Находим конец dest строки
  char *dest_end = dest;
  while (*dest_end != '\0') {
    dest_end++;
  }

  // Копируем символы из src в dest
  while (*src != '\0' && n > 0) {
    *dest_end = *src;
    dest_end++;
    src++;
    n--;
  }

  // Добавляем завершающий нулевой символ
  *dest_end = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  while (*str != '\0' && *str != c) {
    str++;
  }

  return *str == c ? (char *)str : s21_NULL;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && *str2 && *str1 == *str2) {
    str1++;  // Указатель на следующий символ в первой строке
    str2++;  // Указатель на следующий символ во второй строке
  }
  return (int)(unsigned char)(*str1) -
         (int)(unsigned char)(*str2); /* Возвращаем
разницу между символами, на которых мы остановились в строках str1 и str2,
приводя каждый символ к типу unsigned char и вычитая один из другого. */
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;

  if (n > 0) {
    while (*str1 && *str2 && *str1 == *str2 && n > 1) {
      str1++;
      str2++;
      n--;
    }

    result = (int)(unsigned char)(*str1) - (int)(unsigned char)(*str2);
  }

  return result;
}

char *s21_strcpy(char *dest, const char *src) {
  char *ret = dest;  // Создаем указатель ret, который будет указывать на начало
                     // строки dest.
  while ((*dest++ = *src++) != '\0')
    ;  // Копируем символы из строки src в строку dest
  return ret;  // Возвращаем указатель на начало строки dest
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (src != s21_NULL) {
    int i = 0;
    for (; *src && n > 0; src++, i++) {
      dest[i] = *src;
      n--;
    }
    if (n > 0) dest[i] = '\0';
  } else
    dest = s21_NULL;
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char
      *p1 = s21_NULL,
      *p2 = s21_NULL;  // объявляем указатели на символы в строках str1 и str2
  s21_size_t count = 0;  // инициализируем счетчик количества символов в str1 до
                         // первого вхождения символа из str2 значением 0

  int found = 0;  // флаг, указывающий на наличие совпадения символов

  // Цикл проходит по символам в str1 до конца строки или пока не найдется
  // совпадение
  for (p1 = str1; *p1 != '\0' && !found; p1++) {
    // Вложенный цикл проходит по символам в str2 до конца строки
    for (p2 = str2; *p2 != '\0' && !found; p2++) {
      // Если символ в str1 равен символу в str2, устанавливаем флаг
      if (*p1 == *p2) {
        found = 1;
      }
    }
    // Если символ в str1 не был найден в str2, увеличиваем счетчик count на 1
    if (!found) {
      count++;
    }
  }

  // Если ни один символ в str1 не был найден в str2, функция возвращает
  // значение count, которое равно количеству символов в str1
  return count;
}

char *s21_strerror(int errnum) {
  // Статический массив строк с описаниями ошибок
  static const char *strerr[] = s21_error;
  // Статическая строка для неопределенной ошибки длины BUFF_SIZE
  static char s21_undef[BUFF_SIZE] = {'\0'};
  // Указатель на строку результата
  const char *res = s21_NULL;
  // Если номер ошибки вне диапазона
  if (errnum < 0 || errnum >= S21_ERRLIST_SIZE) {
    // Формируем строку для неопределенной ошибки
    s21_sprintf(s21_undef, "Unknown error %d", errnum);
    res = s21_undef;
  } else {
    // Иначе берем описание из массива strerr
    res = strerr[errnum];
  }
  return (char *)res;
}

s21_size_t s21_strlen(const char *str) {
  int len = 0;  // объявляем переменную len и инициализируем ее значением 0

  while (
      str[len] !=
      '\0') {  // перебираем символы в строке, пока не встретим нулевой символ
    len++;     // увеличиваем значение len на 1
  }

  return len;  // возвращаем количество символов в строке
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char
      *p1 = s21_NULL,
      *p2 = s21_NULL;  // объявляем указатели на символы в строках str1 и str2
  int found = 0;  // флаг, указывающий на наличие совпадения символов
  char *rezult = s21_NULL;
  for (p1 = str1; *p1 != '\0' && !found;
       p1++) {  // перебираем символы в строке str1
    for (p2 = str2; *p2 != '\0' && !found;
         p2++) {  // перебираем символы в строке str2
      if (*p1 == *p2) {  // если нашли совпадение символов
        found = 1;
        rezult = (char *)p1;
      }
    }
  }

  return rezult;  // не нашли совпадений, возвращаем s21_NULL
}

char *s21_strrchr(const char *str, int c) {
  const char *last = s21_NULL;
  if (str != s21_NULL) {
    while (*str != '\0') {
      if (*str == c) {
        last = str;
      }
      str++;
    }

    if (*str == c) {
      last = str;
    }
  }
  return (char *)last;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char
      *p1 = s21_NULL,
      *p2 = s21_NULL;  // объявляем указатели для перебора символов в строках
  s21_size_t count = 0;  // инициализируем счетчик количества совпадений
  int flag1 = 0;
  int flag2 = 0;
  // перебираем символы в строке str1
  for (p1 = str1; *p1 != '\0' && !flag1 && !flag2; p1++) {
    for (p2 = str2; *p2 != '\0' && !flag1; p2++) {
      if (*p1 == *p2) {  // если символы совпадают
        count++;  // увеличив��ем счетчик совпадений
        flag1 = 1;  // выходим из вложенного цикла
      }
    }
    if (*p2 == '\0') {  // если не найдено совпадение
      flag2 = 1;  // возвращаем количество совпадений
    }
  }

  return count;  // возвращаем количество совпадений
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *rezult = s21_NULL;

  if (*needle == '\0') {
    rezult =
        (char *)haystack;  // Пустая подстрока всегда найдена в любой строке
  } else {
    int flag = 0;
    while (*haystack != '\0' && !flag) {
      const char *h = haystack;
      const char *n = needle;

      while (*n != '\0' && *h == *n) {
        h++;
        n++;
      }

      if (*n == '\0') {
        rezult = (char *)haystack;  // Подстрока найдена
        flag = 1;
      }
      haystack++;
    }
  }

  return rezult;
}

char *s21_strtok(char *str, const char *delim) {
  static char *lastToken = s21_NULL;  // Последний токен
  char *token = s21_NULL;             // Текущий токен

  // Если функция вызывается с аргументом str равным NULL,
  // то возвращаем NULL, чтобы указать, что больше токенов нет
  if (str == s21_NULL) {
    lastToken = s21_NULL;
    return s21_NULL;
  }

  if (str != s21_NULL) {
    lastToken = str;  // Инициализация lastToken для первого вызова
  }

  int flag2 = 0;

  // Поиск начала токена
  while (*lastToken != '\0' && !flag2) {
    int foundDelimiter = 0;  // Флаг, указывающий на наличие разделителя

    int flag1 = 0;
    // Проверка на наличие разделителя
    for (s21_size_t i = 0; delim[i] != '\0' && !flag1; i++) {
      if (*lastToken == delim[i]) {
        foundDelimiter = 1;
        lastToken++;  // Пропуск разделителя
        flag1 = 1;
      }
    }

    if (!foundDelimiter) {
      flag2 = 1;  // Найден начало токена
    }
  }

  // Запоминаем начало токена
  token = lastToken;

  // Поиск конца токена
  while (*lastToken != '\0') {
    flag2 = 0;
    // Проверка на наличие разделителя
    for (s21_size_t i = 0; delim[i] != '\0' && !flag2; i++) {
      if (*lastToken == delim[i]) {
        *lastToken = '\0';  // Устанавливаем конец токена
        lastToken++;  // Переходим к следующему символу
        flag2 = 1;
      }
    }

    if (!flag2) lastToken++;  // Переходим к следующему символу
  }

  return token;
}

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  if (str != s21_NULL) {
    char *ptr = (char *)str;
    for (s21_size_t i = 0; i < s21_strlen(ptr); i++) {
      if (ptr[i] >= 'a' && ptr[i] <= 'z') {
        ptr[i] -= 32;
      }
    }
    res = ptr;
  }
  return (void *)res;
}

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  if (str != s21_NULL) {
    char *ptr = (char *)str;
    for (s21_size_t i = 0; i < s21_strlen(ptr); i++) {
      if (ptr[i] >= 'A' && ptr[i] <= 'Z') {
        ptr[i] += 32;
      }
    }
    res = ptr;
  }
  return (void *)res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  if (src && str) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);

    if (start_index <= src_len) {
      s21_size_t size =
          src_len + str_len + 1;  // +1 для завершающего нулевого символа
      char *ptr = (char *)calloc(size, sizeof(char));

      if (ptr) {
        s21_strncpy(ptr, src, start_index);
        s21_strcat(ptr, str);
        s21_strcat(ptr, src + start_index);
        res = ptr;
      }
    }
  }
  return (void *)res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (src != s21_NULL) {
    char *str = (char *)src;
    if (trim_chars != s21_NULL) {
      while (s21_strspn(str, trim_chars)) {
        str++;
      }
      s21_size_t len = s21_strlen(str);
      if (len) {
        char *end = str + len;
        while (s21_strspn(--end, trim_chars))
          ;
        *(end + 1) = '\0';
      }
    }
    res = str;
  }
  return (void *)res;
}
