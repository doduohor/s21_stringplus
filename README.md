# s21_string+

## Contents
1. [Chapter I](#chapter-i)
    1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii)
    2.1. [Information](#information)
3. [Chapter III](#chapter-iii)
    3.1. [Part 1](#part-1-реализация-функции-библиотеки-stringh)
    3.2. [Part 2](#part-2-частичная-реализация-функции-sprintf)
    3.3. [Part 3](#part-3-дополнительно-реализация-некоторых-модификаторов-формата-функции-sprintf)
    3.4. [Part 4](#part-4-дополнительно-реализация-функции-sscanf)
    3.5. [Part 5](#part-5-дополнительно-реализация-специальных-функций-обработки-строк)

## Chapter I

## Introduction

В этом проекте вам предстоит создать реализацию библиотеки string.h на языке C с добавлением функций sprintf и sscanf. Этот проект предназначен для улучшения навыков работы со строками и закрепления структурного подхода в программировании.

## Chapter II

## Information

Язык C включает функции для работы со строками в стандартной библиотеке. Они поддерживают операции копирования, конкатенации, поиска и т.д. Строки в C заканчиваются нуль-символом, представляя строку длиной n символов массивом из n + 1 элемента.

### string.h Типы

| № | Переменная | Описание |
| ------ | ------ | ------ |
| 1 | size_t | Целочисленный тип без знака, результат ключевого слова sizeof. |

### string.h Макросы

| № | Макрос | Описание |
| ------ | ------ | ------ |
| 1 | NULL | Макрос, представляющий значение нулевого указателя. |

### string.h Функции

| № | Функция | Описание |
| ------ | ------ | ------ |
| 1 | void *memchr(const void *str, int c, size_t n) | Поиск первого вхождения символа c в первых n байтах строки, на которую указывает str. |
| 2 | int memcmp(const void *str1, const void *str2, size_t n) | Сравнение первых n байтов str1 и str2. |
| 3 | void *memcpy(void *dest, const void *src, size_t n) | Копирование n символов из src в dest. |
| 4 | void *memset(void *str, int c, size_t n) | Копирование символа c в первые n байтов строки, на которую указывает str. |
| 5 | char *strncat(char *dest, const char *src, size_t n) | Добавление строки src к строке dest до n символов. |
| 6 | char *strchr(const char *str, int c) | Поиск первого вхождения символа c в строке str. |
| 7 | int strncmp(const char *str1, const char *str2, size_t n) | Сравнение первых n символов строк str1 и str2. |
| 8 | char *strncpy(char *dest, const char *src, size_t n) | Копирование до n символов из строки src в dest. |
| 9 | size_t strcspn(const char *str1, const char *str2) | Вычисление длины начального сегмента str1, состоящего только из символов, не входящих в str2. |
| 10 | char *strerror(int errnum) | Поиск номера ошибки errnum и возврат указателя на строку с сообщением об ошибке. |
| 11 | size_t strlen(const char *str) | Вычисление длины строки str, не включая завершающий нуль-символ. |
| 12 | char *strpbrk(const char *str1, const char *str2) | Поиск первого символа в str1, который соответствует любому символу из str2. |
| 13 | char *strrchr(const char *str, int c) | Поиск последнего вхождения символа c в строке str. |
| 14 | char *strstr(const char *haystack, const char *needle) | Поиск первого вхождения всей строки needle в строке haystack. |
| 15 | char *strtok(char *str, const char *delim) | Разделение строки str на ряд токенов, разделенных символами из delim. |

### sprintf and sscanf

- int sscanf(const char *str, const char *format, ...) - считывание форматированного ввода из строки.
- int sprintf(char *str, const char *format, ...) - запись форматированного вывода в строку str.

### sprintf and sscanf Спецификаторы

| № | Спецификатор | sprintf | sscanf |
| --- | --- | --- | --- |
| 1 | c | Символ | Символ |
| 2 | d | Знаковое десятичное целое число | Знаковое десятичное целое число |
| 3 | i | Знаковое десятичное целое число | Знаковое целое число |
| 4 | e | Научная нотация | Число с плавающей точкой или научная нотация |
| 5 | E | Научная нотация | Число с плавающей точкой или научная нотация |
| 6 | f | Число с плавающей точкой | Число с плавающей точкой или научная нотация |
| 7 | g | Кратчайшее представление числа | Число с плавающей точкой или научная нотация |
| 8 | G | Кратчайшее представление числа | Число с плавающей точкой или научная нотация |
| 9 | o | Восьмеричное число | Восьмеричное число |
| 10 | s | Строка символов | Строка символов |
| 11 | u | Беззнаковое десятичное целое число | Беззнаковое десятичное целое число |
| 12 | x | Шестнадцатеричное число | Шестнадцатеричное число |
| 13 | X | Шестнадцатеричное число (заглавные буквы) | Шестнадцатеричное число |
| 14 | p | Адрес указателя | Адрес указателя |
| 15 | n | Количество напечатанных символов | Количество считанных символов |
| 16 | % | Символ % | Символ % |

### sprintf Флаги

| № | Флаг | Описание |
| --- | --- | --- |
| 1 | - | Выравнивание по левому краю. |
| 2 | + | Указание знака для положительных чисел. |
| 3 | (пробел) | Добавление пробела перед положительными числами. |
| 4 | # | Специальный режим для некоторых спецификаторов. |
| 5 | 0 | Заполнение числа нулями вместо пробелов. |

### sprintf and sscanf Ширина

| № | Ширина | Описание |
| --- | --- | --- |
| 1 | (число) | Минимальное количество печатаемых символов. |
| 2 | * | Ширина указывается как дополнительный аргумент. |

### sprintf Точность

| № | .точность | Описание |
| --- | --- | --- |
| 1 | .число | Количество знаков для чисел. |
| 2 | .* | Точность указывается как дополнительный аргумент. |

### sprintf and sscanf Длина

| № | Длина | Описание |
| --- | --- | --- |
| 1 | h | Короткое целое число. |
| 2 | l | Длинное целое число или строка широких символов. |
| 3 | L | Длинное число с плавающей точкой. |

### Специальные функции обработки строк

| № | Функция | Описание |
| ------ | ------ | ------ |
| 1 | void *to_upper(const char *str) | Преобразование строки str в верхний регистр. |
| 2 | void *to_lower(const char *str) | Преобразование строки str в нижний регистр. |
| 3 | void *insert(const char *src, const char *str, size_t start_index) | Вставка строки str в src на позиции start_index. |
| 4 | void *trim(const char *src, const char *trim_chars) | Удаление начальных и конечных символов trim_chars из строки src. |

## Chapter III

## Part 1. Реализация функций библиотеки string.h

Необходимо реализовать функции библиотеки string.h:

- Код должен быть написан на языке C стандарта C11 с использованием компилятора gcc.
- Весь код библиотеки, включая заголовочные файлы и make-файлы, должен находиться в папке src ветки develop.
- Следует избегать устаревших конструкций языка и библиотечных функций.
- Код должен соответствовать Google Style.
- Библиотека должна быть оформлена как статическая с заголовочным файлом s21_string.h.
- Код должен быть структурированным и избегать дублирования.
- Для тестирования использовать библиотеку Check, тесты должны покрывать не менее 80% кода.
- Создать Makefile для сборки библиотеки и тестов (цели: all, clean, test, s21_string.a, gcov_report).
- Запрещено использовать стандартную библиотеку string.h, кроме как в unit-тестах.

## Part 2. Частичная реализация функции sprintf

Необходимо реализовать функцию sprintf с поддержкой следующих форматов:

- Спецификаторы: c, d, f, s, u, %
- Флаги: -, +, (пробел)
- Ширина: (число)
- Точность: .(число)
- Длина: h, l

## Part 3. Дополнительно. Реализация некоторых модификаторов формата функции sprintf

Реализация дополнительных модификаторов формата функции sprintf:

- Спецификаторы: g, G, e, E, x, X, o, p
- Флаги: #, 0
- Ширина: *
- Точность: .*
- Длина: L

## Part 4. Дополнительно. Реализация функции sscanf

Реализация функции sscanf с поддержкой полного форматирования.

## Part 5. Дополнительно. Реализация специальных функций обработки строк

Реализация функций обработки строк из класса String.
