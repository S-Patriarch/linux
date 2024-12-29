#include "pl/pl.system"
#include "dcheck.hh"

namespace dcheck {

    DomainChecker::DomainChecker()
    {
        pl::System sys;
        bool islocaleru = sys.is_locale_available("ru_RU");
        if (islocaleru) m_locale = "ru";
    }

    DomainChecker::~DomainChecker() noexcept {}

}
