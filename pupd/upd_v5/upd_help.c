#include <plc/io.h>

void upd_help(void) 
{
        p_cout(
                "Usage: upd [options]\n\n"
                "upd - command line utility.\n"
                "It provides commands to update and clean the system after updating.\n"
                "upd works with package managers such as apt, dnf, pacman, zypper.\n\n"
                "Options:\n"
                "  -f, --full    Updating the system to the latest version followed "
                "by cleaning.\n"
                "  -u, --update  Updating the system to the latest version.\n"
                "  -c, --clean   System cleaning.\n"
        );
}

