#include "pl/pl.system"
#include "dcheck.hh"

namespace dcheck {

    DomainChecker::DomainChecker()
    {
        pl::System sys;
        bool islocaleru = sys.is_locale_available("ru_RU");
        if (islocaleru) m_locale = "ru";
    }

    DomainChecker::~DomainChecker() {}

    auto DomainChecker::set(time_t timeout, int resfile)
        -> void
    {
        m_timeout = timeout;
        m_resfile = resfile;
    }
}
