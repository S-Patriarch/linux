#ifndef DOMAINCHECKER_HH
#define DOMAINCHECKER_HH 3

#include <string>
#include <time.h>

namespace dcheck {

    class DomainChecker {
        time_t m_timeout {5};
        std::string m_fileconfig {"dcheckrc"};
        std::string m_fileresult {"dcheck.res"};

    public:
        DomainChecker();
        ~DomainChecker();

        auto logo() -> void const;
        auto help() -> void const;

        auto set(time_t, int) -> void;
        auto domain_checker(const char *) -> bool const;

        std::string m_locale {"en"};
        int m_resfile {0};
    };

}

#endif
