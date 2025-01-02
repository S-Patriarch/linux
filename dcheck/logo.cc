#include <iostream>
#include "dcheck.hh"

namespace dcheck {

    auto DomainChecker::logo()
        -> void const
    {
        std::cout
            << "       ___  ___  __           __             \n"
            << "      / _ \\/ __\\/ /  ___ ____/ /_____ ____ \n"
            << "     / // / /__/ _ \\/ -_) __/  '_/ -_) __/  \n"
            << "    /____/\\___/_//_/\\__/\\__/_/\\_\\__/_/  \n"
            << "                                             \n"
            << "    v1.1            Created by S-Patriarch     "
            << std::endl;
    }

}
