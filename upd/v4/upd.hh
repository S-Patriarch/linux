#ifndef UPD_HH
#define UPD_HH 3

#include <string>
#include <unordered_map>
#include <vector>

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

    auto is_locale_available(const std::string &) -> bool;
    auto detect_package_manager() -> std::string;

  public:
    std::string m_locale {"en"};
    std::string m_packageManager {};

    UpDate();
    ~UpDate();

    auto logo() -> void const;
    auto help() -> void const;
    auto command_generator(const std::string &) -> std::vector<std::string>;
  };
}

#endif
