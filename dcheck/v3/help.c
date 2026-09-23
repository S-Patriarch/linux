// Copyright (C) 2026, S-Patriarch

void
help(void) P_NOEXCEPT
{
        printf("Usage: dcheck [domain-list-file]\n\n"
               "dcheck - command line utility.\n"
               "It checks the availability and responsiveness of domains.\n"
               "Arbitrary name domain list file. Contains an arbitrary list of\n"
               "domains in the following format:\n"
               "www.google.com\n"
               "www.youtube.com\n");
}
