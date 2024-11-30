#include <array>
#include <memory>
#include <cstdio>
#include "upd.hh"

namespace upd {
  auto UpDate::is_locale_available(const std::string &loc)
    -> bool
  {
    using std::string;
    using std::array;
    using std::shared_ptr;
    using std::fgets;

    array<char,128> buf;
    string res {};

    // выполняем команду locale -a и получаем результат
    shared_ptr<FILE> pipe(popen("locale -a","r"), pclose);
    if (!pipe) return false;

    // читаем вывод команды
    while (fgets(buf.data(), buf.size(), pipe.get()) != nullptr)
      res += buf.data();

    // проверяем, содержится ли нужная локаль в выводе
    return (res.find(loc) != string::npos);
  }
}
