#ifndef UPD_HH
#define UPD_HH

#include <string>

namespace upd {
  class UpDate {
    enum class pm {
      NDEF    = 0,
      APT     = 1, // for Debian, Ubuntu
      DNF_YUM = 2, // for Fedora, RHEL, CentOS
      PACMAN  = 3, // for Arch
      ZYPPER  = 4  // for openSUSE
    };

    std::string _locale; // принимает значение en или ru
    pm _packageManager;  // менеджер пакетов установленный в системе

    auto is_locale_available(const std::string &) -> bool;
    auto detect_package_manager() -> pm;

  public:
    UpDate();
    ~UpDate();

    auto logo() -> void;
    auto help() -> void;
  };
}

#endif
