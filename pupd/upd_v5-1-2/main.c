/* Copyright (C) 2026, S-Patriarch
   upd - утилита командной строки.
   Она предоставляет команды для обновления и очистке системы после обновления.
   upd работает с такими менеджерами пакетов, как apt, dnf, pacman, zypper.  */

#include <ph.h>
#include <plc/plc.h>
#include "version.h"
#include "upd.h"

#include "upd_logo.c"
#include "upd_help.c"
#include "upd_detect_package_manager.c"
#include "upd_command_system.c"

int 
main(int argc, char **argv)
{
        if (argc == 2) {
                struct upd_s upd;
                int res = upd_detect_package_manager(&upd);

                if (res == P_FAILURE) {
                        p_mout("I can't identify the OS\n\n", mess_w, NULL, 
                               "\033[93m");
                } else {
                        if (*upd.upd_pm == '\0') {
                                p_mout("The package manager is not known\n\n", 
                                       mess_w, NULL, "\033[93m");
                        } else {
                                const char *arg = 1[argv];

                                if (strcmp(arg, "-f") == 0       || 
                                    strcmp(arg, "-u") == 0       ||
                                    strcmp(arg, "-c") == 0       ||
                                    strcmp(arg, "--full") == 0   ||
                                    strcmp(arg, "--update") == 0 ||
                                    strcmp(arg, "--clean") == 0) {
                                        p_clrscr();
                                        upd_logo();
                                        putchar((int)'\n');
                                        
                                        p_start_timer();
                                        upd_command_system(&upd, arg);
                                        p_stop_timer();
                                        
                                        putchar((int)'\n');
                                        p_mout("Time spent : ", mess_w, NULL, 
                                               "\033[93m");
                                        printf("%.2f", p_duration_minutes());
                                        p_mout(" minutes\n\n", mess_n, NULL, 
                                               NULL);
                                } else {
                                        p_mout("Command line option [", mess_w, 
                                               NULL, "\033[93m");
                                        printf("%s", arg);
                                        p_mout("] unclear\n\n", mess_n, NULL, 
                                               NULL);
                                }
                        }
                }                        
        } else {
                p_clrscr();
                upd_logo();
                putchar((int)'\n');
                upd_help();
                putchar((int)'\n');
        }

        exit(0);
}

