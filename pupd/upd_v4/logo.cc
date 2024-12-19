#include <iostream>
#include "upd.hh"

namespace upd {
  auto UpDate::logo()
    -> void const
  {
    std::cout
      << "                                             \n"
      << "  |   |       __ \\       |                  \n"
      << "  |   |       |   |      |                   \n"
      << "  |   | __ \\  |   / _` | __|  _ \\          \n"
      << "  \\   | |   | |  / (   | |    __/           \n"
      << " \\___/  .__/ ___/ \\__,_|\\__/\\___\\ 4.0.2 \n"
      << "   By  _| S-Patriarch"
      << std::endl;
  }
}
