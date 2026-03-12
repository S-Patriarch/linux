#include <stdio.h>
#include "ds.h"

void
ds_line(const char *s, int count) P_NOEXCEPT
{
        int     i;

        i = 0;
        for (; i < count; i++)
                printf("%s", s);
}

