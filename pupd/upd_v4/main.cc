/*
 * Copyright (C) 2024, S-Patriarch.
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

    if (pUpDate->get_package_manager()!="") {
      string option {args.at(1)};

      if (option=="-f" || option=="--full"     ||
          option=="-u" || option=="--updating" ||
          option=="-c" || option=="--cleaning") {
        vector<string> commands = pUpDate->command_generator(option);
        cout << pl::mr::clrscr;
        pUpDate->logo();
        cout << endl;
        for (auto &command : commands) {
          system(command.c_str());
        }
      }
      else {
        if (pUpDate->get_locale()=="ru") {
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
      if (pUpDate->get_locale()=="ru") {
        cout
          << "W: пакетный менеджер не известен\n"
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
