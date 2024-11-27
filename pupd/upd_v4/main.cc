/*
 * Copyright (C) 2024, S-Patriarch.
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include "pl/conio"
#include "upd.hh"

using namespace std;

auto main(int argc, char **argv)
  -> int
{
  vector<string> args(argv, argv+argc);
  auto pUpDate = make_unique<upd::UpDate>();

  if (args.size()==2) {
    string option {args.at(1)};
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
