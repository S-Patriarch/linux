#include <plc/io.h>
#include "ds.h"

void 
ds_help(void) P_NOEXCEPT
{
        p_cout( "Usage: ds [path to the directory]\n\n"
                "ds - command line utility.\n"
                "This utility is designed to calculate the directory size.\n"
        );
}

