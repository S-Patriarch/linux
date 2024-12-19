#include <locale>
#include "upd.hh"

namespace upd {
  UpDate::UpDate()
  {
    bool isLocaleRU = is_locale_available("ru_RU");
    if (isLocaleRU) m_locale = "ru";

    m_packageManager = detect_package_manager();
  }

  UpDate::~UpDate() {}
}
