// Copyright (C) 2026, S-Patriarch

#ifndef __DCHECK_H
#define __DCHECK_H      3

P_BEGIN_DECLS

extern void logo (void) P_NOEXCEPT;
extern void help (void) P_NOEXCEPT;

extern unsigned char check_network (void) P_NOEXCEPT;
extern unsigned char check_domain (char *host_name) P_NOEXCEPT;

P_END_DECLS

#endif /* dcheck.h  */
