#ifndef UPD_HH
#define UPD_HH

#include <string>

namespace upd {
  class UpDate {
    std::string _locale; // принимает значение en или ru
    int _packageManager; // менеджер пакетов установленный в системе

    enum class pms {
      apt     = 0, // for Debian, Ubuntu
      dnf_yum = 1, // for Fedora, RHEL, CentOS
      pacman  = 3, // for Arch
      zypper  = 4  // for openSUSE
    };

    auto is_locale_available(const std::string &) -> bool;
    auto detect_package_manager() -> int;

  public:
    UpDate();
    ~UpDate();

    auto logo() -> void;
    auto help() -> void;
  };
}

#endif
