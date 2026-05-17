/*++

    pupd 2.2
    Copyright (c) S-Patriarch, 2023

    Обновление системы Linux семейства Debian.

--*/

#include <iostream>
#include <cstdlib>
#include <string>

typedef signed int s32_t;

//////////////////////////////////////////////////////////////////////
s32_t main(s32_t argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "pupd 2.2\n"
                     "(c) S-Patriarch, 2023\n"
                     "Использование: pupd [параметр]\n\n"
                     "pupd - помошник проведения обновления и очистки системы "
                     "семейства Debian\n"
                     "для людей с очень маленьким опытом работы в ОС Linux.\n\n"
                     "Основные параметры:\n"
                     "  -f  обновление системы до последней версии с последующей "
                     "очисткой\n"
                     "  -u  обновление системы до последней версии\n"
                     "  -c  очистка системы\n";

        return EXIT_SUCCESS;
    }

    std::string  _argString{ *(argv + 1) };

    if (_argString == "-f") {
        //обновление системы до последней версии
        std::system("sudo apt update && sudo apt full-upgrade -y");

        // удаление неиспользуемых программ и ядер
        std::system("sudo apt autoremove -y");

        // удаление старых скаченных файлов архивов
        std::system("sudo apt autoclean -y");

        // удаление скаченных файлов архивов
        std::system("sudo apt clean -y");
    }
    else if (_argString == "-u") {
        // обновление системы до последней версии
        std::system("sudo apt update && sudo apt full-upgrade -y");
    }
    else if (_argString == "-c") {
         // удаление неиспользуемых программ и ядер
         std::system("sudo apt autoremove -y");

         // удаление старых скаченных файлов архивов
         std::system("sudo apt autoclean -y");

         // удаление скаченных файлов архивов
         std::system("sudo apt clean -y");
    }
    else {
        std::cout << "E: Параметр командной строки ["
                  << _argString
                  << "] непонятен."
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
