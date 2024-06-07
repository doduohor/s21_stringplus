#include "s21_string.h"
typedef struct {
  int number_width;
  int star_width;
  char length;
} sscanf_flags;

int gap_processing(int length, char **format_str, sscanf_flags *ss_flags) {
  int flag = 0;
  if (**format_str == '*') {
    ss_flags->star_width = 1;
    (*format_str) += length;
  } else if (s21_strchr(*format_str, '*') == s21_NULL) {
    char numbers[] = "1234567890";
    char flags_length[] = "hlL";
    char rezult_str[sizeof(*format_str)] = {'\0'};
    for (int i = 0; i < length && flag != -1; i++, (*format_str)++) {
      if (s21_strchr(numbers, **format_str) != s21_NULL)
        rezult_str[i] = **format_str;
      else if (s21_strchr(flags_length, **format_str) != s21_NULL)
        ss_flags->length = **format_str;
      else
        flag = 1;
    }
    if (flag != 1) ss_flags->number_width = atoi(rezult_str);
  } else
    flag = 1;
  return flag;
}

int find_distance(char *format_str) {
  char symbols[] = "diecEfgGosuxXpn%";
  int rezult = 0;
  for (int i = 0; s21_strchr(symbols, format_str[i]) == s21_NULL; i++) rezult++;
  return rezult;
}

void specifier_c(char **rezult_str, char **modif_str, sscanf_flags *ss_flags,
                 int *count_success, int space) {
  int count_symbols = 0;  // количество символов, которые надо прочитать
  int i = 0;
  int its_letter = 0;
  if (ss_flags->number_width >
      0)  // если есть значение ширины - меняем количество символов
    count_symbols = ss_flags->number_width;
  else  // иначе приравнием к 1
    count_symbols = 1;
  if (space == 32)  // если перед символом % стоит пробел
  {
    *modif_str = s21_strchr(*modif_str,
                            ' ');  // перекидываем указатель на следующий пробел
    while (**modif_str == ' ' &&
           s21_strlen(*modif_str) >
               1)  // пропускаем все пробелы кроме последнего
      (*modif_str)++;
  }
  while (count_symbols > 0 && **modif_str)  // проходимся
  {
    while (**modif_str == ' ' && space != 32 && count_symbols >= 1 &&
           its_letter == 0) {
      (*modif_str)++;  // сдвигаем указатель строки, из которой берем значения
      count_symbols--;
    }
    if (ss_flags->star_width == 0)
      (*rezult_str)[i] = **modif_str;  // заполняем результирующую строку
    count_symbols--;  // убавляем счетчик символов
    i++;  // свдигаем указатель результирующей строки
    (*modif_str)++;  // сдвигаем указатель строки, из которой берем значения
    its_letter = 1;
  }
  if (ss_flags->star_width == 0)
    (*count_success)++;  // прибавляем счетчик считанных переменных
}

int specifier_d(char **modif_str, long long int *address_rezult,
                sscanf_flags *ss_flags, int *count_success, int minus) {
  int not_numbers =
      0;  // переменная, которая равна нулю пока в строке считывается цифра
  char rezult_str[100] = {
      '\0'};  // создаем массив, куда запишем считанные цифры
  char numbers[] = "1234567890";  // массив возможных цифр (в 10 с.с.)
  int count_numbers = 0, flag = 0, i = 0;
  if (ss_flags->star_width == 0) *address_rezult = 0;
  while (**modif_str == ' ') (*modif_str)++;
  if (ss_flags->number_width > 0)
    count_numbers = ss_flags->number_width;
  else
    for (int k = 0; (*modif_str)[k] != ' ' && (*modif_str)[k]; k++)
      count_numbers++;
  if (minus == -1) {
    rezult_str[i] = '-';
    i++;
  }
  for (; **modif_str && !not_numbers && count_numbers > 0;
       (*modif_str)++, i++, count_numbers--) {
    while ((**modif_str == '0' || **modif_str == '+' || **modif_str == '-') &&
           rezult_str[0] == '\0' && flag == 0) {
      if (**modif_str == '-' || (**modif_str == '0' && count_numbers == 1)) {
        rezult_str[i] = **modif_str;
        i++;
      }
      count_numbers--;
      if (count_numbers > 0)
        (*modif_str)++;
      else
        flag = 1;
    }
    if (s21_strchr(numbers, **modif_str) != s21_NULL && **modif_str &&
        count_numbers > 0)
      rezult_str[i] = **modif_str;
    else
      not_numbers = 1;
  }
  if (ss_flags->star_width == 0) {
    if (ss_flags->length == 'h') {
      int int_value = atoi(rezult_str);
      *address_rezult = (short)int_value;
    } else if (ss_flags->length == 'l') {
      long int *rezult = (long int *)address_rezult;
      *rezult = atol(rezult_str);
    } else if (ss_flags->length == 'L')
      *address_rezult = atoll(rezult_str);
    else
      *address_rezult = (int)atoi(rezult_str);
    if (rezult_str[0] == '\0' ||
        (ss_flags->number_width == 1 && rezult_str[0] == '-'))
      flag = 1;
    else
      (*count_success)++;
  } else {
    *modif_str = s21_strchr(*modif_str, ' ') + 1;
  }
  return flag;
}

void hexToDecimal(char **hex, long long int *rezult_number,
                  sscanf_flags *ss_flags, int *count_success, int minus) {
  int base = 1;
  int i = 0;
  int k = 0;
  int count_number =
      0;  // запоминаем количество символов для перевода указателя
  char rezult_num_str[100] = {'\0'};
  for (int l = 0;
       (*hex)[l] != ' ' && (*hex)[l] && (*hex)[l] != '+' && (*hex)[l] != '-';
       l++)
    if (((*hex)[l] >= '0' && (*hex)[l] <= '9') ||
        ((*hex)[l] >= 'A' && (*hex)[l] <= 'F') ||
        ((*hex)[l] >= 'a' && (*hex)[l] <= 'f'))
      count_number++;
  if (ss_flags->number_width >= 0 && ss_flags->number_width <= count_number)
    i = ss_flags->number_width;
  else
    i = count_number;
  i--;  // понижаем счетчик, так как мы обрабатываем и нулевой символ
  if (rezult_number != s21_NULL)
    *rezult_number =
        0;  // обнуляем переменную, в которую будем записывать результат
  for (; (*hex)[k] != ' ' && (*hex)[k] && k <= i; k++)
    if (((*hex)[k] >= '0' && (*hex)[k] <= '9') ||
        ((*hex)[k] >= 'A' && (*hex)[k] <= 'F') ||
        ((*hex)[k] >= 'a' && (*hex)[k] <= 'f'))
      rezult_num_str[k] = (*hex)[k];
  // Перевод каждого символа из шестнадцатеричной системы в десятичную
  while (i >= 0) {
    // Перевод цифры в десятичное значение
    int digit = 0;
    if (rezult_num_str[i] >= '0' && rezult_num_str[i] <= '9')
      digit = rezult_num_str[i] - '0';
    else if (rezult_num_str[i] >= 'A' && rezult_num_str[i] <= 'F')
      digit = rezult_num_str[i] - 'A' + 10;
    else if (rezult_num_str[i] >= 'a' && rezult_num_str[i] <= 'f')
      digit = rezult_num_str[i] - 'a' + 10;
    // Увеличение десятичного значения
    if (ss_flags->star_width == 0) *rezult_number += digit * base;
    base *= 16;
    i--;
  }
  if (minus == -1) *rezult_number *= -1;
  (*hex) += k;
  if (ss_flags->star_width == 0) (*count_success)++;
}

void octalToDecimal(char **octal, long long int *rezult_number,
                    sscanf_flags *ss_flags, int *count_success, int minus) {
  int base = 1;
  int i = 0;
  int k = 0;
  int count_number =
      0;  // запоминаем количество символов для перевода указателя
  char rezult_num_str[100] = {'\0'};
  for (int l = 0; (*octal)[l] != ' ' && (*octal)[l] && (*octal)[l] != '+' &&
                  (*octal)[l] != '-';
       l++)
    if ((*octal)[l] >= '0' && (*octal)[l] <= '7') count_number++;
  if (ss_flags->number_width > 0 && ss_flags->number_width <= count_number)
    i = ss_flags->number_width;
  else
    i = count_number;
  i--;  // понижаем счетчик, так как мы обрабатываем и нулевой символ
  if (rezult_number != s21_NULL)
    *rezult_number =
        0;  // обнуляем переменную, в которую будем записывать результат
  for (; (*octal)[k] != ' ' && (*octal)[k] && k <= i; k++)
    if ((*octal)[k] >= '0' && (*octal)[k] <= '7')
      rezult_num_str[k] = (*octal)[k];
  // Перевод каждого символа из восьмеричной системы в десятичную
  while (i >= 0) {
    // Перевод цифры в десятичное значение
    int digit = 0;
    digit = rezult_num_str[i] - '0';
    // Увеличение десятичного значения
    if (ss_flags->star_width == 0) *rezult_number += digit * base;
    base *= 8;
    i--;
  }
  if (minus == -1) *rezult_number *= -1;
  (*octal) += k;
  if (ss_flags->star_width == 0) (*count_success)++;
}

int specifier_i(char **modif_str, long long int *address_rezult,
                sscanf_flags *ss_flags, int *count_success) {
  int flag = 0;
  int plus = 0;
  int minus = 1;
  for (int k = 0;
       (*modif_str)[k] && ((*modif_str)[k] == ' ' || (*modif_str)[k] == '+' ||
                           (*modif_str)[k] == '-');
       k++) {
    if ((*modif_str)[k] == ' ' && ss_flags->number_width != 1) (*modif_str)++;
    if ((*modif_str)[k] == '+' && ss_flags->number_width != 1) plus += 1;
    if (((*modif_str)[k] == '-' && ss_flags->number_width != 1)) minus = -1;
    if (((*modif_str)[k] == '+' && ss_flags->number_width != 1) ||
        ((*modif_str)[k] == '-' && ss_flags->number_width != 1))
      (*modif_str)++;
  }
  if (**modif_str == '0') {
    // обрабатываем плюс
    if (plus >= 1) ss_flags->number_width -= 1;
    // если ширина явно указана и не равна одному - сдвигаем указатель и
    // считаем ноль как символ(уменьшаем значение ширины)
    if (ss_flags->number_width != 1) {
      (*modif_str)++;
      ss_flags->number_width -= 1;
    }
    if (**modif_str == 'x' ||
        **modif_str == 'X') {  // обрабатываем 16-ричное число
      (*modif_str)++;
      ss_flags->number_width -= 1;
      hexToDecimal(modif_str, address_rezult, ss_flags, count_success, minus);
    } else
      octalToDecimal(modif_str, address_rezult, ss_flags, count_success, minus);
  } else {
    if (plus == 1) ss_flags->number_width -= 1;
    if (plus != 1 || ss_flags->number_width != 0)
      flag = specifier_d(modif_str, address_rezult, ss_flags, count_success,
                         minus);  // обрабатываем десятичное число
  }
  return flag;
}

int specifier_o(char **modif_str, long long int *address_rezult,
                sscanf_flags *ss_flags, int *count_success) {
  int flag = 0;
  int plus = 0;
  int minus = 1;
  for (int k = 0;
       (*modif_str)[k] && ((*modif_str)[k] == ' ' || (*modif_str)[k] == '+' ||
                           (*modif_str)[k] == '-');
       k++) {
    if ((*modif_str)[k] == ' ' && ss_flags->number_width != 1) (*modif_str)++;
    if ((*modif_str)[k] == '+' && ss_flags->number_width != 1) plus += 1;
    if (((*modif_str)[k] == '-' && ss_flags->number_width != 1)) minus = -1;
    if (((*modif_str)[k] == '+' && ss_flags->number_width != 1) ||
        ((*modif_str)[k] == '-' && ss_flags->number_width != 1))
      (*modif_str)++;
  }
  if (**modif_str == '0') {
    // обрабатываем плюс
    if (plus >= 1) ss_flags->number_width -= 1;
    // если ширина явно указана и не равна одному - сдвигаем указатель и
    // считаем ноль как символ(уменьшаем значение ширины)
    if (ss_flags->number_width != 1) {
      (*modif_str)++;
      ss_flags->number_width -= 1;
    }
  }
  if (**modif_str == '+' || **modif_str == '-' || **modif_str == ' ' ||
      **modif_str > '7')
    count_success--;
  if (ss_flags->star_width == 0)
    octalToDecimal(modif_str, address_rezult, ss_flags, count_success, minus);
  else
    *modif_str = s21_strchr(*modif_str, ' ') + 1;
  return flag;
}

int specifier_x(char **modif_str, long long int *address_rezult,
                sscanf_flags *ss_flags, int *count_success) {
  int flag = 0;
  int plus = 0;
  int minus = 1;
  for (int k = 0;
       (*modif_str)[k] && ((*modif_str)[k] == ' ' || (*modif_str)[k] == '+' ||
                           (*modif_str)[k] == '-');
       k++) {
    if ((*modif_str)[k] == ' ' && ss_flags->number_width != 1) (*modif_str)++;
    if ((*modif_str)[k] == '+' && ss_flags->number_width != 1) plus += 1;
    if (((*modif_str)[k] == '-' && ss_flags->number_width != 1)) minus = -1;
    if (((*modif_str)[k] == '+' && ss_flags->number_width != 1) ||
        ((*modif_str)[k] == '-' && ss_flags->number_width != 1))
      (*modif_str)++;
  }
  if ((*modif_str)[0] == '0' &&
      ((*modif_str)[1] == 'x' || (*modif_str)[1] == 'X')) {
    if (plus >= 1) ss_flags->number_width -= 1;
    if (ss_flags->number_width == 0)
      ss_flags->number_width -= 1;
    else
      ss_flags->number_width -= 2;
    *modif_str += 2;
    hexToDecimal(modif_str, address_rezult, ss_flags, count_success, minus);
  } else {
    if (ss_flags->number_width == 0) ss_flags->number_width -= 1;
    hexToDecimal(modif_str, address_rezult, ss_flags, count_success, minus);
  }
  return flag;
}

void specifier_s(char **rezult_str, char **modif_str, sscanf_flags *ss_flags,
                 int *count_success, int space) {
  int count_symbols = 0;  // количество символов, которые надо прочитать
  int i = 0;
  int its_letter = 0;

  if (ss_flags->number_width >
      0)  // если есть значение ширины - меняем количество символов
    count_symbols = ss_flags->number_width;
  else  // иначе приравнием к 1
  {
    char separators[] = " \t\r";
    int k = 0;
    while ((*modif_str)[k] == ' ') k++;
    for (;
         s21_strchr(separators, (*modif_str)[k]) == s21_NULL && (*modif_str)[k];
         k++)
      count_symbols++;
  }
  if (space == 32)  // если перед символом % стоит пробел
  {
    *modif_str = s21_strchr(*modif_str,
                            ' ');  // перекидываем указатель на следующий пробел
    while (**modif_str == ' ' &&
           s21_strlen(*modif_str) >
               1)  // пропускаем все пробелы кроме последнего
      (*modif_str)++;
  }
  while (count_symbols > 0)  // проходимся
  {
    while (**modif_str == ' ' && space != 32 && its_letter == 0)
      (*modif_str)++;  // сдвигаем указатель строки, из которой берем значения
    if (ss_flags->star_width == 0)
      (*rezult_str)[i] = **modif_str;  // заполняем результирующую строку
    count_symbols--;  // убавляем счетчик символов
    i++;  // свдигаем указатель результирующей строки
    (*modif_str)++;  // сдвигаем указатель строки, из которой берем значения
    its_letter = 1;
  }
  if (ss_flags->star_width == 0)
    (*count_success)++;  // прибавляем счетчик считанных переменных
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list(input);
  va_start(input, format);
  char *format_str = (char *)format;
  char *modif_str = (char *)str;
  int count_success = 0;
  int space = 0;
  int flag = 0;
  int minus = 1;

  while (*format_str &&
         flag != 1)  // проходимся посимвольно по форматной строке пока она не
                     // закончится и не будет ошибки
  {
    if (*format_str == '%') {
      sscanf_flags ss_flags = {0, 0, '\0'};
      format_str++;
      int letter_distance =
          find_distance(format_str);  // находим длину расстояния от % до буквы
      if (letter_distance > 0)  // обрабатываем промежуток
        flag = gap_processing(letter_distance, &format_str, &ss_flags);
      if (flag != 1)  // если все без ошибок, продолжаем работу
      {
        if (*format_str == 'c')  // обрабатываем спецификатор c
        {
          char *rezult_str = s21_NULL;
          if (ss_flags.star_width == 0) rezult_str = va_arg(input, char *);
          specifier_c(&rezult_str, &modif_str, &ss_flags, &count_success,
                      space);
        } else if (*format_str == 'd')  // обрабатываем спецификатор d
        {
          long long int *rez_numb_d = 0;
          if (ss_flags.star_width == 0)
            rez_numb_d = va_arg(input, long long int *);
          flag = specifier_d(&modif_str, rez_numb_d, &ss_flags, &count_success,
                             minus);
        } else if (*format_str == 'i') {
          flag = specifier_i(&modif_str, va_arg(input, long long int *),
                             &ss_flags, &count_success);
        } else if (*format_str == 'o') {
          long long int *rez_numb = 0;
          if (ss_flags.star_width == 0)
            rez_numb = va_arg(input, long long int *);
          flag = specifier_o(&modif_str, rez_numb, &ss_flags, &count_success);
        } else if (*format_str == 'x') {
          long long int *rez_numb = 0;
          if (ss_flags.star_width == 0)
            rez_numb = va_arg(input, long long int *);
          flag = specifier_x(&modif_str, rez_numb, &ss_flags, &count_success);
        } else if (*format_str == 's') {
          char *rezult_str = s21_NULL;
          if (ss_flags.star_width == 0) rezult_str = va_arg(input, char *);
          specifier_s(&rezult_str, &modif_str, &ss_flags, &count_success,
                      space);
        } else {
          format_str++;
        }
      }
    } else {
      space = *format_str;  // запоминаем символ перед знаком %
      format_str++;  // сдвигаем указатель форматной строки
    }
  }
  if (flag == -1) count_success = 0;
  return count_success;  // возвращаем количество считанных символов
}