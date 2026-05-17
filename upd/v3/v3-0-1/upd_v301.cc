/*
 * Copyright (C) 2024, S-Patriarch
 * Обновление системы GNU/Linux семейства Debian Linux.
 */

#include <iostream>
#include <cstdlib>
#include <vector>

#include "pl/conio"

using std::cout;
using std::endl;
using std::exit;

using std::vector;
using std::string;
using std::system;

auto main(int argc, char** argv)
  -> int
{
  vector<string> args(argv,argv+argc);

  auto copyright =[]{
    cout
      << " _    _       _____         _        \n"
      << "| |  | |     |  __ \\       | |       \n"
      << "| |  | |____ | |  \\ \\  __ _| |_  ___ \n"
      << "| |  | |  _ \\| |  ) ) / _' | __|/ _ \\\n"
      << "| \\__/ | |_) | |__/ /| (_| | |_   __/\n"
      << " \\____/|  __/|_____/  \\__,_|\\__/\\___\\ 3.0.1\n"
      << "    By |_| S-Patriarch               \n"
      << endl;
  };

  if (args.size()==2) {
    string opt{args.at(1)};

    if (opt=="-f" || opt=="--full") {
      system("sudo apt update && sudo apt full-upgrade -y");
      system("sudo apt autoremove -y");
      system("sudo apt autoclean -y");
      system("sudo apt clean -y");
    }
    else if (opt=="-u" || opt=="--updating") {
      system("sudo apt update && sudo apt full-upgrade -y");
    }
    else if (opt=="-c" || opt=="--cleaning") {
      system("sudo apt autoremove -y");
      system("sudo apt autoclean -y");
      system("sudo apt clean -y");
    }
    else {
      cout
        << "E: command line option ["
        << opt
        << "] unclear\n"
        << endl;
    }
  }
  else if (args.size()!=2) {
    cout << pl::mr::clrscr;
    copyright();
    cout
      << "Usage: upd [<options>]\n\n"
      << "upd is a assistand for updating and cleaning the system "
      << "of the family Debian Linux\n"
      << "for people with very little experience in OS GNU/Linux.\n\n"
      << "Options:\n"
      << "  -f  --full      Updating the system to the latest "
      << "version followed by cleaning.\n"
      << "  -u  --updating  Updating the system to the latest "
      << "version.\n"
      << "  -c  --cleaning  System cleaning.\n"
      << endl;
  }

  exit(0);
}
