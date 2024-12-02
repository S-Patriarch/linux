#include <locale>
#include "upd.hh"

namespace upd {
  UpDate::UpDate()
  {
    bool isLocaleRU = is_locale_available("ru_RU");
    if (isLocaleRU) locale = "ru";
    else locale = "en";

    packageManager = detect_package_manager();
  }

  UpDate::~UpDate() {}
}
