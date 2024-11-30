#include <iostream>
#include "upd.hh"

namespace upd {
  auto UpDate::help()
    -> void
  {
    using std::cout;
    using std::endl;

    if (_locale=="ru") {
      cout
        << "Использование: upd [<опции>]\n\n"
        << "upd это помощь в обновлении и очистке системы для людей с очень "
        << "небольшим\nопытом работы с ОС GNU/Linux.\n\n"
        << "Опции:\n"
        << "  -f  --full      Обновление системы до последней версии с "
        << "последующей очисткой.\n"
        << "  -u  --updating  Обновление системы до последней версии.\n"
        << "  -c  --cleaning  Очистка системы."
        << endl;
    }
    else {
      cout
        << "Usage: upd [<options>]\n\n"
        << "upd is a system update and cleanup aid for people with very "
        << "little experience\nwith OS GNU/Linux.\n\n"
        << "Options:\n"
        << "  -f  --full      Updating the system to the latest "
        << "version followed by cleaning.\n"
        << "  -u  --updating  Updating the system to the latest "
        << "version.\n"
        << "  -c  --cleaning  System cleaning."
        << endl;
    }
  }
}
