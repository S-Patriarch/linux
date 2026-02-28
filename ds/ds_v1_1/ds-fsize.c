#include <stdio.h>
#include <plc/plcdef.h>
#include "ds.h"

void
ds_fsize(long long size) P_NOEXCEPT 
{
        const char     *units[] = {"B", "KB", "MB", "GB", "TB"};
        int             unit = 0;
        double          dsize = (double)size;

        while (dsize >= 1024 && unit < 4) {
                dsize /= 1024;
                unit++;
        }

        printf("Total size     : %.2f %s\n", dsize, units[unit]);
}

