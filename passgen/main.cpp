/*++

    PassGen
    Copyright (c) S-Patriarch, 2023

    Генератор надежных паролей с записью в файл.
    PassGen запрашивает у пользователя нужную длину и нужное
    количество паролей, а потом все сгенерированные пароли
    отписывает в файл, имя которого он также запросит у пользователя.

--*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <ctime>

typedef signed int s32_t;

//////////////////////////////////////////////////////////////////////
class PassGen
{
public:
    PassGen()  = default;
    ~PassGen() = default;

//--------------------------------------------------------------------
// Выводит логотип.
//
    void
    display_logo()
    { std::cout << "passgen 1.0\n"; }

//--------------------------------------------------------------------
// Запрашивает необходимую информацию.
//
    void
    display_message()
    {
        s32_t _passLenght;
        s32_t _numOfPasswords;
        char* _filename = new char;

        std::cout << "Введите длину пароля для генерации: ";
        std::cin >> _passLenght;

        std::cout << "Введите количество паролей для генерации: ";
        std::cin >> _numOfPasswords;

        std::cout << "Введите имя файла для записи: ";
        std::cin >> _filename;

        std::ofstream outFile;
        outFile.open(_filename, std::ios::out);

        // генерация _numOfPasswords паролей
        for (s32_t k {0}; k < _numOfPasswords; k++) {
            for (s32_t i {0}; i < _passLenght; ++i) {
                num_of_chars(_passLenght);
                pass_generator(_passLenght); // генерация пароля
                outFile << m_password[i];    // запись пароля в файл
            }
            outFile << std::endl;
        }

        outFile.close();

        std::cout << "Пароли успешно сгенерированы и записаны в файл "
                  << _filename
                  << std::endl;
    }

//--------------------------------------------------------------------
// Генерирует пароль заданной длины.
//
    void
    pass_generator(s32_t _passLenght)
    {
        m_password = new char[_passLenght];

        for (s32_t i {0}; i < m_numOfNumbers; ++i) {
            m_password[i] = char(std::rand() % 10 + 48);
        }

        for (s32_t i {m_numOfNumbers}; i < m_numOfNumbers + m_numOfBigChars; ++i) {
            m_password[i] = char(std::rand() % 26 + 65);
        }

        for (s32_t i {m_numOfNumbers + m_numOfBigChars}; i < _passLenght; ++i) {
            m_password[i] = char(std::rand() % 26 + 97);
        }

        // изменяем порядок элементов в заданном диапазоне
        std::random_shuffle(m_password, m_password + _passLenght);
    }

//--------------------------------------------------------------------
    void
    num_of_chars(s32_t _passLenght)
    {
        m_numOfSmallChars = std::rand() % _passLenght;
        s32_t _charRandEnd { _passLenght - m_numOfSmallChars };
        m_numOfBigChars = std::rand() % _charRandEnd;
        m_numOfNumbers = _passLenght - m_numOfSmallChars - m_numOfBigChars;
    }

private:
    s32_t m_numOfSmallChars;
    s32_t m_numOfBigChars;
    s32_t m_numOfNumbers;
    char* m_password;
};

//////////////////////////////////////////////////////////////////////
int main()
{
    std::srand(std::time(NULL));

    PassGen* pass = new PassGen;
    pass->display_logo();    // вывод логотипа
    pass->display_message(); // запрос информации

    return EXIT_SUCCESS;
}
