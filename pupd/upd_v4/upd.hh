#ifndef UPD_HH
#define UPD_HH

#include <string>

namespace upd {
  class UpDate {
    enum class PackageManager {
      ndef    = 0,
      apt     = 1, // for Debian, Ubuntu
      dnf_yum = 2, // for Fedora, RHEL, CentOS
      pacman  = 3, // for Arch
      zypper  = 4  // for openSUSE
    };

    std::string _locale;            // принимает значение en или ru
    PackageManager _packageManager; // менеджер пакетов установленный в системе

    auto is_locale_available(const std::string &) -> bool;
    auto detect_package_manager() -> PackageManager;

  public:
    UpDate();
    ~UpDate();

    auto logo() -> void;
    auto help() -> void;
  };
}

#endif
