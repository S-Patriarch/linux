#ifndef DOMAINCHECKER_HH
#define DOMAINCHECKER_HH 3

#include <string>
#include <time.h>

namespace dcheck {

    class DomainChecker {
        time_t m_timeout {5};

    public:
        DomainChecker();
        ~DomainChecker();

        auto logo() -> void const;
        auto help() -> void const;

        auto set(time_t, int) -> void const;
        auto domain_checker(const char *) -> bool;

        std::string m_locale {"en"};
        int m_resfile {0};
    };

}

#endif
