/*++

    HTML-клинер
    Copyright (c) S-Patriarch, 2023

    HTML представляет собой смесь текста и тегов для его визуального
    отображения. Данная программа очищает HTML-код и выводит лишь
    текст, заключенный в HTML-тегах.

--*/

#include <cstring>
#include <iostream>

typedef unsigned int u32_t;

//--------------------------------------------------------------------
// Функция для парсинга HTML-кода
//
std::string parser(const char* _str)
{
    // храним длину принятой строки
    u32_t _strLen { std::strlen(_str) };

    u32_t _strStart { 0 };
    u32_t _strEnd { 0 };

    // обход строки до символа '>'
    for (u32_t i { 0 }; i < _strLen; i++) {
        // если _str[i] = '>', обновляем _strStart к i+1 и останов
        if (_str[i] == '>') {
            _strStart = i + 1;
            break;
        }
    }

    // удаляем пробел
    while (_str[_strStart] == ' ') { _strStart++; }

    // обход строки до символа '<'
    for (u32_t i { _strStart }; i < _strLen; i++) {
        // если _str[i] = '<', обновляем _strEnd в i-1 и останов
        if (_str[i] == '<') {
            _strEnd = i - 1;
            break;
        }
    }

    // готовим строку к возврату
    std::string _strOutput { };
    for (u32_t i { _strStart }; i <= _strEnd; i++) {
        _strOutput += _str[i];
    }

    return _strOutput;
}

//////////////////////////////////////////////////////////////////////
int main()
{
    const char input1[] { "<h1>Hello, world</h1>" };
    const char input2[] { "<h1>       This is a statement with sone spaces</h1>" };
    const char input3[] { "<p> This is a statement with sone @ #S ., / special characters</p>     " };

    std::cout << "Результат:\n";
    std::cout << ::parser(input1) << std::endl;
    std::cout << ::parser(input2) << std::endl;
    std::cout << ::parser(input3) << std::endl;

    return 0;
}
