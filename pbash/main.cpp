/*++

    pBash
    Copyright (c) S-Patriarch, 2023

    Собственная, хотя и довольно простая, оболочка bash.

--*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef signed int s32_t;

//////////////////////////////////////////////////////////////////////
s32_t main()
{
    std::cout << "pbash 1.0.0\n"
                 "(c) S-Patriarch, 2023\n"
                 "Для выхода из оболочки pbash введите exit\n\n";

    char _commandExit[] { "exit" };

    for (;;) {
        std::cout << "pbash: ";

        char _command[BUFSIZ];
        std::memset(&_command[0], 0, BUFSIZ);

        std::cin.getline(_command, BUFSIZ);

        if (_command[0] == _commandExit[0]) { return EXIT_SUCCESS; }

        // создаю вектор аргументов argv[] для
        // системной функции execvp()

        std::vector<std::string> argv { };

        // инициализирую вектор аргументов
        s32_t i { 0 };
        std::string _strTemp { };
        while (_command[i] != '\0') {
            if (_command[i] != ' ') {
                _strTemp += _command[i];
            }
            else {
                argv.push_back(_strTemp);
                _strTemp = "";
            }
            ++i;
        }
        argv.push_back(_strTemp);

        // преобразую std::vector<std::string> в
        // std::vector<char*> для системной функции execvp()
        std::vector<char*> args { };
        for (auto& arg : argv) {
            args.push_back(&arg[0]);
        }

        args.push_back((char*)nullptr);

        // формирую указатель на массив char*, который будет
        // использоваться в execvp() как char**
        char** _charArgv = args.data();

        pid_t _pid { };
        if ((_pid = fork()) == 0) {
            execvp(_charArgv[0], _charArgv);
        }

        s32_t _status { };
        while (wait(&_status) != _pid) {
            continue;
        }

        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
