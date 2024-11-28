/*
 * Copyright (C) 2024, S-Patriarch.
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include "pl/conio"
#include "upd.hh"

auto main(int argc, char **argv)
  -> int
{
  using std::cout;
  using std::endl;

  std::vector<std::string> args(argv, argv+argc);
  auto pUpDate = std::make_unique<upd::UpDate>();

  if (args.size()==2) {
    std::string option {args.at(1)};
  }
  else {
    cout << pl::mr::clrscr;
    pUpDate->logo();
    cout << endl;
    pUpDate->help();
    cout << endl;
  }

  std::exit(0);
}
