#include <iostream>
#include "upd.hh"

namespace upd {
  auto UpDate::logo()
    -> void const
  {
    std::cout
      << "        __ __    ___       __         \n"
      << "       / // /___/ _ \\___ _/ /____    \n"
      << "      / // / _ / // / _  / __/ -_)    \n"
      << "      \\___/ __/____/\\_,_/\\__/\\__/ \n"
      << "    v4.3 /_/ Created by S-Patriarch     "
      << std::endl;
  }
}
