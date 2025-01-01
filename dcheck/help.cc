#include <iostream>
#include "dcheck.hh"

namespace dcheck {

    auto DomainChecker::help()
        -> void const
    {
        using std::cout;
        using std::endl;

        if (m_locale=="ru") {
            cout
                << "Использование: dcheck [параметры] [файл списка доменов]\n\n"
                << "dcheck - утилита командной строки.\n"
                << "Она проверяет доступность и отзывчивость доменов.\n"
                << "Файл списка доменов произвольного наименования. Содержит произвольный\n"
                << "список доменов следующего формата:\n"
                << "www.google.com\n"
                << "www.youtube.com\n\n"
                << "Параметры:\n"
                << "  -r    Отписывать результат работы в файл.\n"
                << "  -h    Помощь."
                << endl;
        }
        else {
            cout
                << "Usage: dcheck [options] [domain list file]\n\n"
                << "dcheck - command line utility.\n"
                << "It checks the availability and responsiveness of domains.\n"
                << "Arbitrary name domain list file. Contains an arbitrary list of\n"
                << "domains in the following format:\n"
                << "www.google.com\n"
                << "www.youtube.com\n\n"
                << "Options:\n"
                << "  -r    Write the result of the work to a file.\n"
                << "  -h    Help."
                << endl;
        }
    }

}
