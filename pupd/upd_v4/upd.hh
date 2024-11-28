#ifndef UPD_HH
#define UPD_HH

#include <string>
#include <unordered_map>

namespace upd {
  class UpDate {
    std::unordered_map<std::string,std::string> ospm {
      {"debian",   "apt"},
      {"ubuntu",   "apt"},
      {"fedora",   "dnf"},
      {"rhel",     "dnf"},
      {"centos",   "dnf"},
      {"arch",     "pacman"},
      {"opensuse", "zypper"}
    };

    std::string _locale;
    std::string _packageManager;

    auto is_locale_available(const std::string &) -> bool;
    auto detect_package_manager() -> std::string;

  public:
    UpDate();
    ~UpDate();

    auto logo() -> void;
    auto help() -> void;
    auto command_generator() -> void;
  };
}

#endif
