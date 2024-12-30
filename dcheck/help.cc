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
                << "Она проверяет доступность и отзывчивость доменов.\n\n"
                << "Параметры:\n"
                << "  -r    Отписывать результат работы в файл.\n"
                << "  -h    Помощь."
                << endl;
        }
        else {
            cout
                << "Usage: dcheck [options] [domain list file]\n\n"
                << "dcheck - command line utility.\n"
                << "It checks the availability and responsiveness of domains.\n\n"
                << "Options:\n"
                << "  -r    Write the result of the work to a file.\n"
                << "  -h    Help."
                << endl;
        }
    }

}
