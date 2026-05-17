#include "upd.hh"

namespace upd {
  auto UpDate::command_generator(const std::string &option)
    -> std::vector<std::string>
  {
    std::vector<std::string> commands;

    if (m_packageManager=="apt") {
      if (option=="-f" || option=="--full") {
        commands.emplace_back("sudo apt update");
        commands.emplace_back("sudo apt full-upgrade -y");
        commands.emplace_back("sudo apt autoremove -y");
        commands.emplace_back("sudo apt autoclean -y");
        commands.emplace_back("sudo apt clean -y");
      }
      if (option=="-c" || option=="--clean") {
        commands.emplace_back("sudo apt autoremove -y");
        commands.emplace_back("sudo apt autoclean -y");
        commands.emplace_back("sudo apt clean -y");
      }
      if (option=="-u" || option=="--update") {
        commands.emplace_back("sudo apt update");
        commands.emplace_back("sudo apt full-upgrade -y");
      }
    }

    if (m_packageManager=="dnf") {
      if (option=="-f" || option=="--full") {
        commands.emplace_back("sudo dnf check-update");
        commands.emplace_back("sudo dnf upgrade --refresh -y");
        commands.emplace_back("sudo dnf autoremove -y");
        commands.emplace_back("sudo dnf clean all -y");
      }
      if (option=="-c" || option=="--clean") {
        commands.emplace_back("sudo dnf autoremove -y");
        commands.emplace_back("sudo dnf clean all -y");
      }
      if (option=="-u" || option=="--update") {
        commands.emplace_back("sudo dnf check-update");
        commands.emplace_back("sudo dnf upgrade --refresh -y");
      }
    }

    if (m_packageManager=="pacman") {
      if (option=="-f" || option=="--full") {
        commands.emplace_back("sudo pacman -Syu --noconfirm");
        commands.emplace_back("sudo pacman -Rns --noconfirm");
        commands.emplace_back("sudo pacman -Sc --noconfirm");
      }
      if (option=="-c" || option=="--clean") {
        commands.emplace_back("sudo pacman -Rns --noconfirm");
        commands.emplace_back("sudo pacman -Sc --noconfirm");
      }
      if (option=="-u" || option=="--update") {
        commands.emplace_back("sudo pacman -Syu --noconfirm");
      }
    }

    if (m_packageManager=="zypper") {
      if (option=="-f" || option=="--full") {
        commands.emplace_back("sudo zypper refresh");
        commands.emplace_back("sudo zypper update -y");
        commands.emplace_back("sudo zypper clean --all");
      }
      if (option=="-c" || option=="--clean") {
        commands.emplace_back("sudo zypper clean --all");
      }
      if (option=="-u" || option=="--update") {
        commands.emplace_back("sudo zypper refresh");
        commands.emplace_back("sudo zypper update -y");
      }
    }

    return commands;
  }
}
