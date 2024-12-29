#include <iostream>
#include "dcheck.hh"

namespace dcheck {

    auto DomainChecker::help()
        -> void const
    {
        std::cout
            << "help..."
            << std::endl;
    }

}
