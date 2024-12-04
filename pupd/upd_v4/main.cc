/*
 * Copyright (C) 2024, S-Patriarch.
 *
 * upd - утилита командной строки.
 * Она предоставляет команды для обновления и очистке системы после обновления.
 * upd работает с такими менеджерами пакетов, как apt, dnf, pacman, zypper.
 */

#include <iostream>
#include <cstdlib>
#include <memory>
#include "pl/conio"
#include "upd.hh"

auto main(int argc, char **argv)
  -> int
{
  using std::cout;
  using std::endl;
  using std::exit;

  using std::string;
  using std::vector;
  using std::system;

  vector<string> args(argv, argv+argc);
  auto pUpDate = std::make_unique<upd::UpDate>();

  if (args.size()==2) {

    if (pUpDate->m_packageManager!="") {
      string option {args.at(1)};

      if (option=="-f" || option=="--full"   ||
          option=="-u" || option=="--update" ||
          option=="-c" || option=="--clean") {
        vector<string> commands = pUpDate->command_generator(option);
        cout << pl::mr::clrscr;
        pUpDate->logo();
        cout << endl;
        for (auto &command : commands) {
          system(command.c_str());
        }
        cout << endl;
      }
      else {
        if (pUpDate->m_locale=="ru") {
          cout
            << "W: опция командной строки ["
            << option
            << "] неясна\n"
            << endl;
        }
        else {
          cout
            << "W: command line option ["
            << option
            << "] unclear\n"
            << endl;
        }
      }
    }
    else {
      if (pUpDate->m_locale=="ru") {
        cout
          << "W: пакетный менеджер неизвестен\n"
          << endl;
      }
      else {
        cout
          << "W: the package manager is not known\n"
          << endl;
      }
    }
  }
  else {
    cout << pl::mr::clrscr;
    pUpDate->logo();
    cout << endl;
    pUpDate->help();
    cout << endl;
  }

  exit(0);
}
