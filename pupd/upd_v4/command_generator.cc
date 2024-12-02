#include "upd.hh"

namespace upd {
  auto UpDate::command_generator(const std::string &option)
    -> std::vector<std::string>
  {
    std::vector<std::string> commands;

    if (packageManager == "apt") {
      if (option=="-f" || option=="--full") {
        commands.push_back("sudo apt update && sudo apt full-upgrade -y");
        commands.push_back("sudo apt autoremove -y");
        commands.push_back("sudo apt autoclean -y");
        commands.push_back("sudo apt clean -y");
      }
      if (option=="-c" || option=="--clean") {
        commands.push_back("sudo apt autoremove -y");
        commands.push_back("sudo apt autoclean -y");
        commands.push_back("sudo apt clean -y");
      }
      if (option=="-u" || option=="--update") {
        commands.push_back("sudo apt update && sudo apt full-upgrade -y");
      }
    }

    if (packageManager == "dnf") {
      if (option=="-f" || option=="--full") {
        //commands.push_back("sudo apt update && sudo apt full-upgrade -y");
        //commands.push_back("sudo apt autoremove -y");
        //commands.push_back("sudo apt autoclean -y");
        //commands.push_back("sudo apt clean -y");
      }
      if (option=="-c" || option=="--clean") {
        //commands.push_back("sudo apt autoremove -y");
        //commands.push_back("sudo apt autoclean -y");
        //commands.push_back("sudo apt clean -y");
      }
      if (option=="-u" || option=="--update") {
        //commands.push_back("sudo apt update && sudo apt full-upgrade -y");
      }
    }

    if (packageManager == "pacman") {
      if (option=="-f" || option=="--full") {
        //commands.push_back("sudo apt update && sudo apt full-upgrade -y");
        //commands.push_back("sudo apt autoremove -y");
        //commands.push_back("sudo apt autoclean -y");
        //commands.push_back("sudo apt clean -y");
      }
      if (option=="-c" || option=="--clean") {
        //commands.push_back("sudo apt autoremove -y");
        //commands.push_back("sudo apt autoclean -y");
        //commands.push_back("sudo apt clean -y");
      }
      if (option=="-u" || option=="--update") {
        //commands.push_back("sudo apt update && sudo apt full-upgrade -y");
      }
    }

    if (packageManager == "zypper") {
      if (option=="-f" || option=="--full") {
        //commands.push_back("sudo apt update && sudo apt full-upgrade -y");
        //commands.push_back("sudo apt autoremove -y");
        //commands.push_back("sudo apt autoclean -y");
        //commands.push_back("sudo apt clean -y");
      }
      if (option=="-c" || option=="--clean") {
        //commands.push_back("sudo apt autoremove -y");
        //commands.push_back("sudo apt autoclean -y");
        //commands.push_back("sudo apt clean -y");
      }
      if (option=="-u" || option=="--update") {
        //commands.push_back("sudo apt update && sudo apt full-upgrade -y");
      }
    }

    return commands;
  }
}
