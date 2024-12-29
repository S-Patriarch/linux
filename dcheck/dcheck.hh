#ifndef DOMAINCHECKER_HH
#define DOMAINCHECKER_HH 3

#include <string>

namespace dcheck {

    class DomainChecker {
    public:
        DomainChecker();
        ~DomainChecker() noexcept;

        auto logo() -> void const;
        auto help() -> void const;

        auto domain_checker(const char *) -> bool const;

        std::string m_locale {"en"};
        std::string m_fileresult {"dcheck.res"};
        int m_resfile {0};
    };

}

#endif
