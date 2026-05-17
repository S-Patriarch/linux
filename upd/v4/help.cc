#include <iostream>
#include "upd.hh"

namespace upd {
  auto UpDate::help()
    -> void const
  {
    using std::cout;
    using std::endl;

    if (m_locale=="ru") {
      cout
        << "Использование: upd [параметры]\n\n"
        << "upd - утилита командной строки.\n"
        << "Она предоставляет команды для обновления и очистке системы после "
        << "обновления.\n"
        << "upd работает с такими менеджерами пакетов, как apt, dnf, pacman, "
        << "zypper.\n\n"
        << "Параметры:\n"
        << "  -f, --full    Обновление системы до последней версии с "
        << "последующей очисткой.\n"
        << "  -u, --update  Обновление системы до последней версии.\n"
        << "  -c, --clean   Очистка системы."
        << endl;
    }
    else {
      cout
        << "Usage: upd [options]\n\n"
        << "upd - command line utility.\n"
        << "It provides commands to update and clean the system after updating.\n"
        << "upd works with package managers such as apt, dnf, pacman, zypper.\n\n"
        << "Options:\n"
        << "  -f, --full    Updating the system to the latest version followed "
        << "by cleaning.\n"
        << "  -u, --update  Updating the system to the latest version.\n"
        << "  -c, --clean   System cleaning."
        << endl;
    }
  }
}
