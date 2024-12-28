#include <iostream>
#include "dcheck.hh"

namespace dcheck {

    auto DomainChecker::logo()
        -> void const
    {
        std::cout
            << "                                                                                  \n"
            << "  __  \\                   _)        ___| |                |                      \n"
            << "  |   |                            /     |                |                       \n"
            << "  |   |  _ \\   \\   |  _` | | __ \\  |     __ \\   _ \\   __| |  /   _ \\  __ \\ \n"
            << "  |  /  (   | .  . | (   | | |   | \\     |   |  __/  (      <    __/  |          \n"
            << " ___/  \\___/__|\\/ _|\\__,_|_|_|  _|\\____|_|  _|\\___\\ \\___|_| _\\ \\___\\ _| \n"
            << " By S-Patriarch                             github.com/S-Patriarch   1.0.0"
            << std::endl;
    }

}
