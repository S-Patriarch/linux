#include <stdio.h>
#include "dcheck.h"

void dch_help(void)
{
        printf("Usage: dcheck [domain list file]\n\n"
               "dcheck - command line utility.\n"
               "It checks the availability and responsiveness of domains.\n"
               "Arbitrary name domain list file. Contains an arbitrary list of\n"
               "domains in the following format:\n"
               "www.google.com\n"
               "www.youtube.com\n\n");
}

