#include <locale>
#include "upd.hh"

namespace upd {
  UpDate::UpDate()
  {
    bool isLocaleRU = is_locale_available("ru_RU");
    if (isLocaleRU) _locale = "ru";
    else _locale = "en";

    _packageManager = detect_package_manager();
  }

  UpDate::~UpDate() {}

  auto UpDate::get_locale()
    -> std::string const
  {return _locale;}

  auto UpDate::get_package_manager()
    -> std::string const
  {return _packageManager;}
}
