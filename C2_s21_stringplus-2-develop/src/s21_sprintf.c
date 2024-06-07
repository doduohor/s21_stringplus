#include "s21_string.h"
int s21_sprintf(char *str, const char *format, ...) {
  // Объект для обработки переменного числа аргументов
  va_list args;
  // Инициализируем объект аргументами функции
  va_start(args, format);
  // Указатель на текущую позицию в выходной строке
  char *p = str;
  // Повторяем, пока не достигнем конца формата строки
  while (*format != '\0') {
    // Если встретили символ '%'
    if (*format == '%') {
      format++;  // Переходим к следующему символу
      s21_process_format(&format, args, &p);
    } else {
      // Если в форматной строке обычный символ, просто добавляем его в
      // результат
      *p++ = *format;
    }
    // Переходим к следующему символу формата
    format++;
  }
  // Добавляем завершающий нулевой символ в результат
  *p = '\0';
  // Освобождаем va_list
  va_end(args);
  // Возвращаем количество символов в результирующей строке
  return p - str;
}

// парсим форматы
void s21_process_format(const char **format, va_list args, char **p) {
  // Создаем структуру format_spec и заполняем ее параметрами форматирования
  format_spec spec;
  int parsed = s21_parse_format_spec(format, &spec, args);
  if (parsed < 0) {
    // Ошибка разбора спецификатора формата
    **p = '\0';
    return;
  }
  // Обрабатываем символ после '%'
  switch (**format) {
    case 'd':
      *p = s21_print_int(args, *p, &spec);
      break;
    case 'c':
      *p = s21_print_char(args, *p, &spec);
      break;
    case 's':
      *p = s21_print_str(args, *p, &spec);
      break;
    case 'f':
      *p = s21_print_float(args, *p, &spec);
      break;
    case 'x':
      *p = s21_print_hex(args, *p, &spec);
      break;
    case 'X':
      *p = s21_print_hex_upper(args, *p, &spec);
      break;
    case 'u':
      *p = s21_print_ten(args, *p, &spec);
      break;
    case 'o':
      *p = s21_print_oct(args, *p, &spec);
      break;
    case 'e':
    case 'E':
      *p = s21_print_exp(args, *p, &spec, *format);
      break;
    case 'p':
      *p = s21_print_pointer(args, *p, &spec);
      break;
    case '%':
      *p = s21_print_procent(*p);
      break;
    default:
      // Для неизвестных форматов просто добавляем символ в результат
      *(*p)++ = **format;
      break;
  }
}

// парсим флаги
void s21_parse_flags(const char **format, format_spec *spec) {
  // Парсинг флагов формата
  int parsing = 1;
  // Цикл парсинга флагов формата
  while (parsing) {
    switch (**format) {
      case '-':
        spec->minus_flag = 1;
        break;  // Флаг выравнивания по левому краю
      case '+':
        spec->plus_flag = 1;
        break;  // Флаг отображения знака "+" для положительных чисел
      case ' ':
        spec->space_flag = 1;
        break;  // Флаг отображения пробела для положительных чисел без знака
      case '#':
        spec->sharp_flag = 1;
        break;
      case '0':
        spec->zero_flag = (!spec->minus_flag ? 1 : 0);
        break;
      default:
        parsing = 0;
        break;  // Завершение парсинга флагов
    }
    // Если цикл парсинга флагов еще не завершен, переходим к следующему символу
    if (parsing) {
      (*format)++;  // Переход к следующему символу
    }
  }
}

// Проверяет, является ли символ цифрой
int s21_my_isdigit(char c) {
  // Возвращает true, если символ находится
  // в диапазоне от '0' до '9' включительно
  return (c >= '0' && c <= '9');
}

// Разбор ширины поля
void s21_parse_width(const char **format, format_spec *spec, va_list args) {
  // Если следующий символ - цифра или '0'
  if (**format == '*') {
    (*format)++;
    spec->width = va_arg(args, unsigned int);
  } else if (s21_my_isdigit(**format) || **format == '0') {
    // Задаём начальное значение ширины как 0
    spec->width = 0;
    // Пока символ является цифрой или нолём
    while (s21_my_isdigit(**format) || **format == '0') {
      // Получаем очередную цифру ширины
      spec->width = spec->width * 10 + (**format - '0');
      // Переводим указатель на следующий символ
      (*format)++;
    }
  }
}

// Разбор точности
void s21_parse_precision(const char **format, format_spec *spec, va_list args) {
  // Если следующий символ - точка
  if (**format == '.') {
    // Переводим указатель на следующий символ
    (*format)++;
    if (**format == '*') {
      (*format)++;
      spec->precision = va_arg(args, unsigned int);
    } else {
      // Задаём начальное значение точности как 0
      spec->precision = 0;
      // Пока символ является цифрой или нулём
      while (s21_my_isdigit(**format) || **format == '0') {
        // Получаем очередную цифру и добавляем к текущей точности
        spec->precision = spec->precision * 10 + (**format - '0');
        // Переводим указатель на следующий символ
        (*format)++;
      }
    }
  }
}

// Разбор модификатора длины
void s21_parse_length_modifier(const char **format, format_spec *spec) {
  // Если следующий символ - модификатор длины h, l или L
  if (**format == 'h' || **format == 'l' || **format == 'L') {
    // Запоминаем модификатор в спецификации
    spec->length_modifier = **format;
    // Переводим указатель на следующий символ
    (*format)++;
  }
}

// исполнение всех специфиакторов формата
int s21_parse_format_spec(const char **format, format_spec *spec,
                          va_list args) {
  // Инициализация структуры спецификатора формата
  spec->minus_flag = 0;  // Флаг выравнивания по левому краю
  spec->plus_flag = 0;  // Флаг отображения знака "+" для положительных чисел
  // Флаг отображения пробела для положительных чисел без знака
  spec->space_flag = 0;
  spec->width = -1;           // Ширина поля
  spec->precision = -1;       // Точность
  spec->length_modifier = 0;  // Модификатор длины
  spec->sharp_flag = 0;
  spec->zero_flag = 0;
  // Парсинг флагов формата
  s21_parse_flags(format, spec);
  // Парсинг ширины поля
  s21_parse_width(format, spec, args);
  // Парсинг точности
  s21_parse_precision(format, spec, args);
  // Парсинг модификатора длины
  s21_parse_length_modifier(format, spec);
  // Получаем спецификатор формата
  spec->format_specifier = **format;
  // Возвращаем 0, чтобы указать, что парсинг успешно завершен
  return 0;
}

int s21_get_num_zeros(int precision, int len) {
  // Проверяем, что точность больше или равна 0 и больше, чем длина.
  if (precision >= 0 && precision > len) {
    // Если проверка прошла успешно, возвращаем разницу между precision и len.
    return precision - len;
  }
  // Если проверка не прошла, возвращаем 0.
  return 0;
}

int s21_get_num_spaces(int width, int len, int num_zeros, bool negative) {
  // Проверяем, что ширина (width) больше 0 и длина, количество нулей и знак
  // занимают меньше места, чем ширина.
  if (width > 0 && (len + num_zeros + (negative ? 1 : 0)) < width) {
    // Если проверка прошла успешно, возвращаем разницу между шириной и
    // количеством занимаемых символов.
    return width - (len + num_zeros + (negative ? 1 : 0));
  }
  // Если проверка не прошла, возвращаем 0.
  return 0;
}

void s21_print_sign(char **p, char sign) {
  // Проверяем, что знак не равен 0 (т.е. задан).
  if (sign != 0) {
    // Если проверка прошла успешно, записываем знак в значение, на которое
    // указывает указатель *p, и сдвигаем указатель на следующую позицию.
    **p = sign;
    *p += 1;
  }
}

void s21_print_zeros(char **p, int num_zeros) {
  // Инициализируем переменную i значением 0. Запускаем цикл, который будет
  // выполняться, пока значение i меньше num_zeros. На каждой итерации цикла
  // значение i увеличивается на 1.
  for (int i = 0; i < num_zeros; i++) {
    // Значению, на которое указывает указатель *p, присваиваем символ '0'.
    // Таким образом, мы записываем нули в позицию, на которую указывает
    // указатель *p.
    **p = '0';
    // Сдвигаем указатель *p на следующую позицию, чтобы в будущем можно было
    // записать следующий символ.
    *p += 1;
  }
  // Когда цикл завершается, функция print_zeros завершается. В результате в
  // строку записывается указанное количество нулей.
}

void s21_print_space(char **p, int num_spaces, char fill_char) {
  // Инициализируем переменную i значением 0. Запускаем цикл, который будет
  // выполняться, пока значение i меньше num_spaces. На каждой итерации цикла
  // значение i увеличивается на 1.
  for (int i = 0; i < num_spaces; i++) {
    // Значению, на которое указывает указатель *p, присваиваем значение
    // fill_char. Таким образом, мы записываем символ заполнения в позицию, на
    // которую указывает указатель *p.
    **p = fill_char;
    // Сдвигаем указатель *p на следующую позицию, чтобы в будущем можно было
    // записать следующий символ.
    *p += 1;
  }
  // Когда цикл завершается, функция print_space завершается. В результате в
  // строке записывается указанное количество символов заполнения.
}

char space_zero(format_spec *spec) {
  char fill_char;
  if (spec->zero_flag) {
    fill_char = '0';
  } else {
    fill_char = ' ';
  }
  return fill_char;
}

char *s21_print_int(va_list args, char *p, format_spec *spec) {
  char buffer[32] = {'\0'};  // буфер для хранения числа как строки
  int len = 0;                      // длина строки числа
  int width = spec->width;          // ширина поля вывода
  int precision = spec->precision;  // точность вывода
  int num_spaces = 0;  // количество пробелов перед числом
  int num_zeros = 0;  // количество нулей перед числом
  char fill_char = space_zero(spec);  // символ заполнения поля
  bool negative = false;  // флаг отрицательного числа

  if (spec->length_modifier == 'l') {  // проверяем наличие длинной модификации
    long int num = va_arg(args, long int);  // принимаем аргумент типа long int
    negative = num < 0;  // проверяем, отрицательное ли число
    s21_itoa_d(num, buffer, 10);  // преобразуем число в строку
  } else if (spec->length_modifier == 'h') {
    // проверяем наличие короткой модификации
    // принимаем аргумент типа short int
    short int num = (short int)va_arg(args, int);
    negative = num < 0;  // проверяем, отрицательное ли число
    s21_itoa_d(num, buffer, 10);  // преобразуем число в строку
  } else {                        // если модификаций нет
    int num = va_arg(args, int);  // принимаем аргумент типа int
    negative = num < 0;  // проверяем, отрицательное ли число
    s21_itoa_d(num, buffer, 10);  // преобразуем число в строку
  }
  len = s21_strlen(buffer);  // вычисляем длину строки числа
  if (precision >= 0 && precision < len) {  // проверяем, нужна ли точность
    precision = len;  // если да, устанавливаем точность в длину строки
  }
  num_zeros = s21_get_num_zeros(precision, len);  // вычисляем количество нулей
  // вычисляем количество пробелов
  num_spaces = s21_get_num_spaces(width, len, num_zeros, negative);
  int sign =
      negative ? '-' : (spec->plus_flag ? '+' : (spec->space_flag ? ' ' : 0));
  if (spec->zero_flag) {
    s21_print_sign(&p, sign);
  }
  if (!spec->minus_flag) {  // если нет флага выравнивания по левому краю
    s21_print_space(&p, num_spaces, fill_char);  // выводим пробелы перед числом
  }
  if (!spec->zero_flag) {
    s21_print_sign(&p, sign);
  }
  // выводим знак числа
  s21_print_zeros(&p, num_zeros);  // выводим нули перед числом
  s21_strcpy(p, buffer);  // копируем строку числа в выходной буфер
  p += len;  // увеличиваем указатель на длину строки числа
  if (spec->minus_flag) {  // если установлен флаг выравнивания по левому краю
    s21_print_space(&p, num_spaces, fill_char);  // выводим пробелы после числа
  }
  return p;  // возвращаем указатель на конец выходного буфера
}

// Печатаем заданное кол-во пробелов
void s21_print_spaces(int num_spaces, char **p) {
  for (int i = 0; i < num_spaces; i++) {  // цикл по количеству пробелов
    *(*p)++ = ' ';  // записываем пробел в выходной буфер и сдвигаем указатель
  }
}

// Функция для печати символа
char *s21_print_char(va_list args, char *p, format_spec *spec) {
  // Получаем символ
  char c = (char)va_arg(args, int);
  // принимаем аргумент типа int и преобразуем его к типу char
  // Ширина поля width
  int width = spec->width;  // получаем ширину поля из спецификатора формата
  // Если ширина больше 1
  if (width > 1) {
    // Вычисляем кол-во пробелов для дополнения
    // вычисляем количество пробелов для дополнения до заданной ширины
    int num_spaces = width - 1;
    // В зависимости от флага "-" располагаем символ и пробелы
    if (spec->minus_flag) {  // если установлен флаг выравнивания по левому краю
      *p++ = c;  // записываем символ в выходной буфер и сдвигаем указатель
      s21_print_spaces(num_spaces, &p);  // выводим заданное количество пробелов
    } else {  // если флаг выравнивания по левому краю не установлен
      s21_print_spaces(num_spaces, &p);  // выводим заданное количество пробелов
      *p++ = c;  // записываем символ в выходной буфер и сдвигаем указатель
    }
  } else {  // если ширина поля равна 1
    // Иначе просто печатаем символ
    *p++ = c;  // записываем символ в выходной буфер и сдвигаем указатель
  }
  // Возвращаем указатель
  return p;  // возвращаем указатель на конец выходного буфера
}

// Получаем строку из аргументов переменной длины, если она не является NULL,
// иначе возвращаем строку "(null)"
const char *s21_get_string(va_list args) {
  // получаем строку из аргументов переменной длины
  const char *s = va_arg(args, const char *);
  if (s == s21_NULL) {  // проверяем, является ли строка NULL
    s = "(null)";  // если является, возвращаем строку "(null)"
  }
  return s;  // возвращаем строку
}

// Получаем длину строки
int s21_get_len(const char *s) { return s21_strlen(s); }

// Получаем точность для вывода строки
int s21_get_precision(format_spec *spec, int len) {
  // получаем точность из спецификатора формата
  int precision = spec->precision;
  // если точность задана и меньше длины строки
  if (precision >= 0 && precision < len) {
    return precision;  // возвращаем точность
  }
  return len;  // иначе возвращаем длину строки
}

// Получаем ширину поля для вывода строки
int s21_get_width(format_spec *spec, int len) {
  int result = len;
  int width = spec->width;  // получаем ширину поля из спецификатора формата
  // если ширина поля задана и меньше длины строки
  if (width > 0 && len < width) {
    result = width;  // возвращаем ширину поля
  }
  return result;  // иначе возвращаем длину строки
}

// Выводим заданное количество символов fill_char в выходной буфер
void s21_print_fill_chars(char **p, int num_fill, char fill_char) {
  // цикл по количеству заполняемых символов
  for (int i = 0; i < num_fill; i++) {
    **p = fill_char;  // записываем символ в выходной буфер
    *p += 1;  // сдвигаем указатель на следующий символ в выходном буфере
  }
}

// Функция для печати строки
char *s21_print_str(va_list args, char *p, format_spec *spec) {
  const char *s = s21_get_string(args);  // получаем строку для вывода
  int len = s21_get_len(s);  // получаем длину строки
  int precision = s21_get_precision(spec, len);  // получаем точность вывода
  int width = s21_get_width(spec, precision);  // получаем ширину поля вывода
  if (!spec->minus_flag) {  // если флаг выравнивания по левому краю
                            // неустановлен
    // выводим заданное количество пробелов перед строкой
    s21_print_fill_chars(&p, width - precision, ' ');
  }
  // копируем заданное количество символов из строки в выходной буфер
  s21_strncpy(p, s, precision);
  p += precision;  // сдвигаем указатель на следующий символ в выходном буфере
  if (spec->minus_flag) {  // если флаг выравнивания по левому краю установлен
    // выводим заданное количество пробелов после строки
    s21_print_fill_chars(&p, width - precision, ' ');
  }
  return p;  // возвращаем указатель на конец выходного буфера
}

// Вычисляем значение для округления
double s21_compute_rounding(int precision) { return 0.5 * pow(10, -precision); }

// Разбиваем число на целую и дробную части
void s21_split_number(long double num, long long *int_part,
                      long double *fract_part) {
  *int_part = (long long)num;     // целая часть числа
  *fract_part = num - *int_part;  // дробная часть числа
}

// Конвертируем целую часть числа в строку
int s21_convert_integer_to_string(long long int_part, char *int_str) {
  int integer_len = 0;
  if (int_part == 0) {  // если целая часть числа равна 0
    int_str[integer_len++] = '0';  // записываем в строку символ '0'
  } else {
    while (int_part > 0) {  // пока целая часть числа больше 0
      // записываем в строку последнюю цифру числа
      int_str[integer_len++] = (int)(int_part % 10) + '0';
      int_part /= 10;  // уменьшаем целую часть числа на один разряд
    }
    // переворачиваем строку с цифрами
    for (int i = 0; i < integer_len / 2; i++) {
      char temp = int_str[i];
      int_str[i] = int_str[integer_len - i - 1];
      int_str[integer_len - i - 1] = temp;
    }
  }
  return integer_len;  // возвращаем длину строки с целой частью числа
}

// Конвертируем дробную часть числа в строку
int s21_convert_fract_to_string(double fract_part, int precision,
                                char *fract_str) {
  int fract_len = 0;
  if (precision > 0) {  // если точность вывода больше 0
    // записываем в строку символ точки
    fract_str[fract_len++] = '.';
    // цикл по количеству цифр в дробной части числа
    for (int i = 0; i < precision; i++) {
      fract_part *= 10.0;  // умножаем дробную часть на 10
      // получаем цифру
      int digit = (int)fract_part;
      // записываем цифру в строку
      fract_str[fract_len++] = digit + '0';
      fract_part -= digit;  // вычитаем записанную цифру из дробной части
    }
  }
  return fract_len;  // возвращаем длину строки с дробной частью числа
}

// Добавляем знак числа
void s21_add_sign(char **p, int sign, format_spec *spec) {
  // если число отрицательное или задан флаг "+" или " "
  if (sign < 0 || spec->plus_flag || spec->space_flag) {
    // добавляем соответствующий знак
    *(*p)++ = sign < 0 ? '-' : spec->plus_flag ? '+' : ' ';
  }
}

// Добавляем целую и дробную части числа в выходной буфер
void s21_add_parts(char **p, char *int_str, int integer_len, char *fract_str,
                   int fract_len, int precision) {
  // копируем строку с целой частью числа в выходной буфер
  s21_memcpy(*p, int_str, integer_len);
  // сдвигаем указатель на конец скопированных символов
  *p += integer_len;

  if (precision > 0) {  // если задана точность вывода
    // копируем строку с дробной частью числа в выходной буфер
    s21_memcpy(*p, fract_str, fract_len);
    *p += fract_len;  // сдвигаем указатель на конец скопированных символов
  }
}

// Функция для вывода числа с плавающей точкой
char *s21_print_float(va_list args, char *p, format_spec *spec) {
  // получаем аргумент из списка переменных аргументов
  char fill_char = spec->zero_flag ? '0' : ' ';
  long double num = get_double(args, spec);
  // получаем значение точности вывода
  int precision = spec->precision == -1 ? 6 : spec->precision;
  // получаем значение ширины поля вывода
  int width = spec->width;
  // вычисляем значение для округления
  double rounding = s21_compute_rounding(precision);
  int sign = num < 0 ? -1 : 1;  // определяем знак числа
  num = fabsl(num + sign * rounding);  // округляем число
  long long int_part = 0;
  long double fract_part = 0;
  // разбиваем число на целую и дробную части
  s21_split_number(num, &int_part, &fract_part);
  char int_str[256] = {'\0'};
  // конвертируем целую часть числа в строку
  int integer_len = s21_convert_integer_to_string(int_part, int_str);
  char fract_str[256] = {'\0'};
  // конвертируем дробную часть числа в строку
  int fract_len = s21_convert_fract_to_string(fract_part, precision, fract_str);
  int minus = 0;
  if (precision == 0 && spec->sharp_flag) {
    s21_strcat(int_str, ".");
    integer_len++;
  }
  // вычисляем общую длину числа
  int total_len = integer_len + (precision > 0 ? fract_len : 0);
  // если задан знак числа, либо флаги "+" или " "
  if (sign < 0 || spec->plus_flag || spec->space_flag) {
    total_len++;  // увеличиваем общую длину числа на единицу
  }
  if (spec->minus_flag) {  // если задан флаг "-"
    minus = 1;             // устанавливаем флаг "минус"
  } else {
    if (spec->zero_flag) {
      s21_add_sign(&p, sign, spec);  // добавляем знак числа
    }
    if (width > total_len) {  // если ширина поля вывода больше длины числа
      // вычисляем количество символов для добавления
      int padding_len = width - total_len;
      s21_memset(p, fill_char, padding_len);  // добавляем пробелы или нули
      p += padding_len;  // сдвигаем указатель на конец добавленных символов
    }
  }
  if (!spec->zero_flag) {
    s21_add_sign(&p, sign, spec);  // добавляем знак числа
  }
  // добавляем целую и дробную части числа в выходной буфер
  s21_add_parts(&p, int_str, integer_len, fract_str, fract_len, precision);
  // если задан флаг "-"
  if (minus == 1) {
    // добавляем пробелы для выравнивания поля вывода
    for (int i = 0; i < width - total_len; i++) {
      *p++ = fill_char;
    }
  }
  *p = '\0';  // добавляем символ конца строки в конец выходного буфера
  return p;  // возвращаем указатель на конец выходного буфера
}

// Заполняет буфер числом, преобразованным в нужную систему счисления
char *s21_buffer_fill(char *q, unsigned long int num, int base,
                      char start_letter) {
  // Пока число num не станет равно нулю
  do {
    // Берет остаток от деления числа на базу (последнюю цифру)
    unsigned int digit = num % base;
    // Уменьшает указатель q - помещает символ цифры в конец буфера
    *--q = digit < 10 ? '0' + digit : start_letter + digit - 10;
    // Цифра меньше 10 - просто помещаем '0' + значение цифры
    // Иначе берем start_letter и добавляем разницу для текущей цифры
    // Делит чисел на базу (извлекает следующую цифру)
    num /= base;
    // Проверяем, стало ли число равно нулю
  } while (num != 0);
  // Возвращаем указатель на начало заполненного буфера
  return q;
}
// Печать число
char *s21_print_number(char *p, char *q, int len, format_spec *spec,
                       char flag) {
  if (spec->sharp_flag || flag == 'p') {
    if (flag == 'x' || flag == 'X' || flag == 'p') {
      char temp[50] = {'\0'};
      s21_strcpy(temp, p);
      // Копируем str2 в str1
      if (flag == 'x' || flag == 'p') {
        s21_strcpy(p, "0x");
      } else if (flag == 'X') {
        s21_strcpy(p, "0X");
      }
      // Добавляем сохраненную строку temp в конец str1
      s21_strcat(p, temp);
      p += 2;
    }
  }
  // num_zeros - кол-во ведущих нулей, в зависимости от точности
  int num_zeros = spec->precision > len ? spec->precision - len : 0;
  // num_pad_chars - кол-во символов-заполнителей до ширины поля
  int num_pad_chars =
      spec->width > len + num_zeros ? spec->width - (len + num_zeros) : 0;
  // Если флаг "-", то заполнитель будет пробел. Иначе 0.
  char pad_char =
      (spec->zero_flag && spec->precision <= 0 && !(spec->minus_flag)) ? '0'
                                                                       : ' ';
  // Если флаг "-"
  if (spec->minus_flag) {
    // Печатаем ведущие нули
    for (int i = 0; i < num_zeros; i++) {
      *p++ = '0';
    }
    // Печатаем цифры числа
    while (*q) {
      *p++ = *q++;
    }
    // Печатаем пробелы
    for (int i = 0; i < num_pad_chars; i++) {
      *p++ = ' ';
    }
  } else {
    // Печатаем заполнители
    for (int i = 0; i < num_pad_chars; i++) {
      *p++ = pad_char;
    }
    // Печатаем ведущие нули
    for (int i = 0; i < num_zeros; i++) {
      *p++ = '0';
    }
    // Печатаем цифры числа
    while (*q) {
      *p++ = *q++;
    }
  }
  // Возвращаем указатель за последним напечатанным символом
  return p;
}

// Получить число
unsigned long int s21_get_number(va_list args, format_spec *spec) {
  // Переменная для хранения числа
  unsigned long int num = 0;
  // Выбор типа для извлечения числа в зависимости от указателя длины
  if (spec->length_modifier == 'l') {
    // l - unsigned long int
    num = va_arg(args, unsigned long int);
  } else if (spec->length_modifier == 'h') {
    // h - unsigned short int
    num = (unsigned short int)va_arg(args, unsigned int);
  } else {
    // По умолчанию - unsigned int
    num = va_arg(args, unsigned int);
  }
  // Возврат полученного числа
  return num;
}

// Напечатать число в шестнадцатиричном формате
char *s21_print_hex(va_list args, char *p, format_spec *spec) {
  char flag = 'x';
  // Получить число в нужной разрядности
  unsigned long int num = s21_get_number(args, spec);
  // Буфер для преобразования числа в шестнадцатиричную строку
  char buffer[32] = {'\0'};
  // Указатель на конец буфера
  char *q = buffer + sizeof(buffer) - 1;
  // Начальное значение указателя - пустая строка
  *q = '\0';
  // Преобразовать число в шестнадцатиричную строку, начиная с конца буфера
  q = s21_buffer_fill(q, num, 16, 'a');
  // Длина строки - размер буфера минус адрес указателя q
  int len = buffer + sizeof(buffer) - 1 - q;
  // Используем функцию для форматирования строки с цифрами
  return s21_print_number(p, q, len, spec, flag);
}

// Напечатать число в шестнадцатиричном формате с буквами в верхнем регистре
char *s21_print_hex_upper(va_list args, char *p, format_spec *spec) {
  char flag = 'X';
  // Получить число
  unsigned long int num = s21_get_number(args, spec);
  // Буфер для преобразования числа
  char buffer[32] = {'\0'};
  // Указатель на конец буфера
  char *q = buffer + sizeof(buffer) - 1;
  // Начальное значение указателя - пустая строка
  *q = '\0';
  // Вызываем функцию заполнения буфера, но используем 'A' вместо 'a'
  q = s21_buffer_fill(q, num, 16, 'A');
  // Длина строки
  int len = buffer + sizeof(buffer) - 1 - q;
  // Используем функцию для форматирования строки с цифрами
  return s21_print_number(p, q, len, spec, flag);
}

// Напечатать десятичное число
char *s21_print_ten(va_list args, char *p, format_spec *spec) {
  // Получить число
  unsigned long int num = s21_get_number(args, spec);
  // Буфер
  char buffer[32] = {'\0'};
  // Указатель на конец буфера
  char *q = buffer + sizeof(buffer) - 1;
  // Начальное значение указателя - пустая строка
  *q = '\0';
  // Преобразовать число в десятичную строку, начиная с конца буфера
  q = s21_buffer_fill(q, num, 10, '0');
  // Длина строки
  int len = buffer + sizeof(buffer) - 1 - q;
  // Используем функцию для форматирования строки с цифрами
  return s21_print_number(p, q, len, spec, 'u');
}

// Добавить "%" в строку результата
char *s21_print_procent(char *p) {
  *p++ = '%';
  return p;
}

// Функция для проверки корректности основания системы счисления
int s21_is_valid_base(int base) { return base >= 2 && base <= 36; }

// Функция для обработки отрицательных чисел и установки флага знака
int s21_handle_negative(long int *value) {
  int is_negative = 0;
  // Если значение отрицательное, устанавливаем флаг и меняем знак числа на
  // обратный
  if (*value < 0) {
    is_negative = 1;
    *value = -(*value);
  }
  // Возвращаем флаг знака числа
  return is_negative;
}

// Функция для записи цифрр числа в обратном порядке в строку
int s21_write_digits(long int value, char *str, int base) {
  // Символы для представления чисел в разных системах счисления
  static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i = 0;
  do {
    str[i++] = digits[value % base];  // Записываем символ в строку
    value /= base;  // Делим число на основание системы счисления
  } while (value);  // Повторяем, пока число не станет равным 0
  return i;  // Возвращаем количество записанных символов
}

// Функция для переворачивания строки
void s21_reverse_string(char *str, int len) {
  for (int i = 0; i < len / 2; i++) {  // Идем до середины строки
    // Сохраняем текущий символ в переменную temp
    char temp = str[i];
    // Меняем местами символы с начала и конца строки
    str[i] = str[len - i - 1];
    // Заменяем символ в конце строки на символ в начале строки
    str[len - i - 1] = temp;
  }
}

char *s21_itoa_d(long int value, char *str, int base) {
  if (!s21_is_valid_base(base)) {
    // Возвращаем пустую строку, если основание системы счисления некорректно
    *str = '\0';
    return str;
  }
  // Обрабатываем отрицательные числа и устанавливаем флаг знака
  s21_handle_negative(&value);
  // Записываем цифры числа в обратном порядке в строку
  int num_digits = s21_write_digits(value, str, base);
  str[num_digits] = '\0';  // Добавляем нуль-символ в конец строки
  s21_reverse_string(str, num_digits);  // Переворачиваем строку
  return str;  // Возвращаем указатель на строку
}

char *s21_print_oct(va_list args, char *p, format_spec *spec) {
  unsigned long int num = 0;
  num = s21_get_number(args, spec);
  char buffer[100] = {'\0'};
  char *oct_num = buffer;
  char fill_char = space_zero(spec);
  while (num != 0) {
    // Получаем очередную цифру числа в 16-ричной системе счисления
    int digit = num % 8;
    *oct_num++ = '0' + digit;
    num /= 8;
  }
  if (spec->sharp_flag) {
    *oct_num++ = '0';
  }
  int len = oct_num - buffer;
  int width = spec->width;
  // Вычисляем количество нулей, которые нужно добавить
  int num_zeros = width - len;
  if (!spec->minus_flag) {
    if (width > 0 && len < width) {
      for (int i = 0; i < num_zeros; i++) {
        *p++ = fill_char;
      }
    }
  }
  while (oct_num > buffer) {
    *p++ = *--oct_num;
  }
  if (spec->minus_flag) {
    if (width > 0 && len < width) {
      for (int i = 0; i < num_zeros; i++) {
        *p++ = fill_char;
      }
    }
  }
  return p;
}

void exp_suffix(char *exp_str, int exp_precision, char e_symb) {
  exp_str[0] = e_symb;
  if (exp_precision < 0) {
    exp_str[1] = '-';
    exp_precision *= (-1);
  } else {
    exp_str[1] = '+';
  }
  if (exp_precision < 10) {
    exp_str[2] = '0';
    exp_str[3] = '0' + exp_precision;
  } else if (exp_precision < 100) {
    exp_str[2] = '0' + (exp_precision / 10);
    exp_str[3] = '0' + (exp_precision % 10);
  } else if (exp_precision < 1000) { /*999*/
    exp_str[2] = '0' + (exp_precision / 100);
    exp_str[3] = '0' + ((exp_precision / 10) % 10);
    exp_str[4] = '0' + (exp_precision % 10);
  }
}

long double get_double(va_list args, format_spec *spec) {
  // Переменная для хранения числа
  long double num = 0;
  // Выбор типа для извлечения числа в зависимости от указателя длины
  if (spec->length_modifier == 'L') {
    // l - unsigned long int
    num = va_arg(args, long double);

  } else {
    // По умолчанию - unsigned int
    num = va_arg(args, double);
  }
  // Возврат полученного числа
  return num;
}

void convert_to_exp(int *exp_precision, long double *num) {
  if (fabsl((double)((int)(*num))) < 1) {
    while (fabsl((double)((int)(*num))) < 1) {
      (*exp_precision)--;
      *num *= 10;
    }
  } else {
    while (fabsl((double)((int)(*num))) > 9) {
      (*exp_precision)++;
      *num /= 10;
    }
  }
}

char *s21_print_exp(va_list args, char *p, format_spec *spec,
                    const char *format) {
  long double num = 0;
  num = get_double(args, spec);
  char e_symb = *format;
  int precision = spec->precision == -1 ? 6 : spec->precision;
  int width = spec->width;
  double rounding = s21_compute_rounding(precision);
  int sign = num < 0 ? -1 : 1;
  char fill_char = space_zero(spec);
  // Приведение целой части к экспоненциальному виду
  int exp_precision = 0;
  convert_to_exp(&exp_precision, &num);
  num = fabsl(num + sign * rounding);
  // Разбиваем число на целую и дробную части
  long long int_part = (long long)num;
  double fract_part = num - int_part;
  // Преобразуем целую часть в строку
  char int_str[3] = {'\0'};
  int integer_len = (precision == 0 && spec->sharp_flag) ? 2 : 1;
  int_str[0] = '0' + (int)(int_part % 10);
  if (precision == 0 && spec->sharp_flag) {
    int_str[1] = '.';
  }
  // Преобразуем дробную часть в строку
  char fract_str[100] = {'\0'};
  int fract_len = s21_convert_fract_to_string(fract_part, precision, fract_str);
  // Создаем строку для записи экспоненты
  int exp_len = exp_precision < 100 ? 4 : 5;
  char exp_str[6] = {'\0'};
  exp_suffix(exp_str, exp_precision, e_symb);
  // Вычисляем общую длину строки
  int total_len = integer_len + (precision > 0 ? fract_len : 0) + exp_len;
  if (sign < 0 || spec->plus_flag || spec->space_flag) {
    total_len++;
  }
  int align = 0;
  if (spec->minus_flag) {
    align = 1;
  } else {
    if (spec->zero_flag) {
      s21_add_sign(&p, sign, spec);
    }
    if (width > total_len) {
      int padding_len = width - total_len;
      s21_memset(p, fill_char, padding_len);
      p += padding_len;
    }
  }
  if (!spec->zero_flag) {
    s21_add_sign(&p, sign, spec);  // добавляем знак числа
  }
  s21_add_parts(&p, int_str, integer_len, fract_str, fract_len, precision);
  s21_memcpy(p, exp_str, exp_len);
  p += exp_len;
  if (align == 1) {
    for (int i = 0; i < width - total_len; i++) {
      *p++ = ' ';
    }
  }
  *p = '\0';
  return p;
}

char *s21_print_pointer(va_list args, char *p, format_spec *spec) {
  // Получить число в нужной разрядности
  uintptr_t num = va_arg(args, uintptr_t);
  // Буфер для преобразования числа в шестнадцатиричную строку
  char buffer[32] = {'\0'};
  // Указатель на конец буфера
  char *q = buffer + sizeof(buffer) - 1;
  // Начальное значение указателя - пустая строка
  *q = '\0';
  // Преобразовать число в шестнадцатиричную строку,
  // начиная с конца буфера
  q = s21_buffer_fill(q, num, 16, 'a');
  int len = buffer + sizeof(buffer) - 1 - q + (spec->sharp_flag ? 2 : 0);
  // Используем функцию для форматирования строки с цифрами
  return s21_print_number(p, q, len, spec, 'p');
}
