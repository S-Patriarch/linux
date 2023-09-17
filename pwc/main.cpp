/*++

    WordCount for Linux 1.0.0
    Copyright (c) S-Patriarch, 2023

    pWordCount подсчитывает количество символов/слов/строк в
    текстовом файле.
    Программа читает данные со стандартного ввода, следовательно,
    на ее ввод можно отправить любой вывод.

Использование:
    @code

    ...$ sudo dmesg | ./pwc
    или
    ...$ cat <имя файла> | ./pwc

    @endcode

--*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cctype>

typedef signed int s32_t;

//////////////////////////////////////////////////////////////////////
s32_t main()
{
    s32_t _countChars { 0 }; // количество символов
    s32_t _countWords { 0 }; // количество слов
    s32_t _countLines { 0 }; // количество строк

    s32_t _inSpace { 1 };    // счетчик пробелов
    s32_t _last { '\n' };    // последний считанный символ
    s32_t _ch { };           // считанный символ

    while ((_ch = getchar()) != EOF) {
        _last = _ch;
        _countChars++; // увеличиваю счетчик количества символов

        if (isspace(_ch)) {
            _inSpace = 1;
            if (_ch == '\n') {
                _countLines++; // увеличиваю счетчик количества строк
            }
        } else {
            _countWords += _inSpace; // увеличиваю счетчик количества слов
            _inSpace = 0;            // обнуляю счетчик пробелов
        }
    }

    if (_last != '\n') {
        // учитываю последнию строку
        _countLines++;
    }

    std::cout << "WordCount for Linux 1.0.0\n"
                 "Copyright (c) S-Patriarch, 2023\n\n";
    std::cout << "строк\tслов\tсимволов\n";
    std::cout << _countLines << '\t'
              << _countWords << '\t'
              << _countChars << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
