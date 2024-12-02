#include <iostream>
#include "upd.hh"

namespace upd {
  auto UpDate::logo()
    -> void
  {
   using std::cout;
   using std::endl;

   cout
      << " _    _       _____         _        \n"
      << "| |  | |     |  __ \\       | |       \n"
      << "| |  | |____ | |  \\ \\  __ _| |_  ___ \n"
      << "| |  | |  _ \\| |  ) ) / _' | __|/ _ \\\n"
      << "| \\__/ | |_) | |__/ /| (_| | |_   __/\n"
      << " \\____/|  __/|_____/  \\__,_|\\__/\\___\\ 4.0.0\n"
      << "    By |_| S-Patriarch"
      << endl;
  }
}
