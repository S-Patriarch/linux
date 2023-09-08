/*++

    HTML-клинер
    Copyright (c) S-Patriarch, 2023

    HTML представляет собой смесь текста и тегов для его визуального
    отображения. Данная программа очищает HTML-код и выводит лишь
    текст, заключенный в HTML-тегах.

--*/

#include <cstring>
#include <iostream>
#include <fstream>

typedef unsigned int u32_t;

//--------------------------------------------------------------------
// Функция для парсинга HTML-кода
//
std::string parser(const char* _str)
{
    // храним длину принятой строки
    u32_t _strLen = std::strlen(_str);

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
int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " [файл]\n"
                  << "Пример:\n"
                  << '\t' << argv[0] << " index.html"
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string _argString { *(argv + 1) };
    std::string _strIn { };
    std::string _strOut { };

    std::ifstream fIn;
    fIn.open(_argString);

    if (!fIn.is_open()) {
        std::cerr << "E: Не могу открыть целевой файл."
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::ofstream fOut;
    fOut.open("result.out", std::ios::app);

    while (std::getline(fIn, _strIn)) {
        _strOut = ::parser(_strIn.c_str());
        fOut << _strOut
             << '\n';
    }

    fIn.close();
    fOut.close();

    return 0;
}
