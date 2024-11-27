#include <array>
#include <memory>
#include "upd.hh"

using namespace std;

namespace upd {
  auto UpDate::is_locale_available(const string &loc)
    -> bool
  {
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
