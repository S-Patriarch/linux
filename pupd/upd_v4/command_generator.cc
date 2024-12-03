#include "upd.hh"

namespace upd {
  auto UpDate::command_generator(const std::string &option)
    -> std::vector<std::string>
  {
    std::vector<std::string> commands;

    if (m_packageManager=="apt") {
      if (option=="-f" || option=="--full") {
        commands.emplace_back("sudo apt update && sudo apt full-upgrade -y");
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
        commands.emplace_back("sudo apt update && sudo apt full-upgrade -y");
      }
    }

    if (m_packageManager=="dnf") {
    }

    if (m_packageManager=="pacman") {
    }

    if (m_packageManager=="zypper") {
    }

    return commands;
  }
}
