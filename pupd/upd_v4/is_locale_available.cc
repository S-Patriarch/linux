#include <array>
#include <memory>
#include <cstdio>
#include "upd.hh"

namespace upd {
  auto UpDate::is_locale_available(const std::string &loc)
    -> bool
  {
    std::array<char,128> buf;
    std::string res {};

    // выполняем команду locale -a и получаем результат
    std::shared_ptr<FILE> pipe(popen("locale -a","r"), pclose);
    if (!pipe) return false;

    // читаем вывод команды
    while (std::fgets(buf.data(), buf.size(), pipe.get()) != nullptr)
      res += buf.data();

    // проверяем, содержится ли нужная локаль в выводе
    return (res.find(loc) != std::string::npos);
  }
}
