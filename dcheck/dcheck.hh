#ifndef DOMAINCHECKER_HH
#define DOMAINCHECKER_HH 3

#include <string>

namespace dcheck {

    class DomainChecker {
        std::string m_fileconfig {"dcheckrc"};
        std::string m_fileresult {"dcheck.res"};

    public:
        DomainChecker();
        ~DomainChecker();

        auto logo() -> void const;
        auto help() -> void const;

        auto domain_checker(const char *) -> bool const;
        auto read_configuration() -> void;

        std::string m_locale {"en"};
        int m_resfile {0};
    };

}

#endif
