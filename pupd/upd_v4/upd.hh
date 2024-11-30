#ifndef UPD_HH
#define UPD_HH

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

    std::string _locale;
    std::string _packageManager;

    auto is_locale_available(const std::string &) -> bool;
    auto detect_package_manager() -> std::string;

  public:
    UpDate();
    ~UpDate();

    auto get_locale() -> std::string const;
    auto get_package_manager() -> std::string const;

    auto logo() -> void;
    auto help() -> void;
    auto command_generator(const std::string &) -> std::vector<std::string>;
  };
}

#endif
