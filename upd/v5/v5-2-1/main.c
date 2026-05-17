// Copyright (C) 2026, S-Patriarch

/* upd - утилита командной строки.
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
#include "upd_network_check.c"

int 
main(int argc, char *argv[])
{
        if (argc == 2) {
                p_clrscr();
                upd_logo();
                putchar((int)'\n');

                if (strcmp(1[argv], "-f") == 0     || 
                    strcmp(1[argv], "-u") == 0     ||
                    strcmp(1[argv], "--full") == 0 ||
                    strcmp(1[argv], "--update") == 0) {
                        p_mout("Checking network... ", mess_w, NULL, 
                               "\033[93m");

                        unsigned char is_check = upd_network_check();
                        if (is_check == P_FALSE) {
                                p_mout("[FAILED]\n", mess_n, NULL, 
                                       "\033[93m");
                                p_mout("No internet connection\n\n", mess_e, 
                                       NULL, "\033[93m");
                                exit(P_FAILURE);
                        }

                        p_mout("[  OK  ]\n\n", mess_n, NULL, "\033[93m");
                }

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
                                if (strcmp(1[argv], "-f") == 0       || 
                                    strcmp(1[argv], "-u") == 0       ||
                                    strcmp(1[argv], "-c") == 0       ||
                                    strcmp(1[argv], "--full") == 0   ||
                                    strcmp(1[argv], "--update") == 0 ||
                                    strcmp(1[argv], "--clean") == 0) {
                                        
                                        p_timer_start();
                                        upd_command_system(&upd, 1[argv]);
                                        p_timer_stop();
                                        
                                        putchar((int)'\n');
                                        p_mout("Time spent: ", mess_w, NULL, 
                                               "\033[93m");
                                        printf("%.2f", p_duration_minutes());
                                        p_mout(" minutes\n\n", mess_n, NULL, 
                                               NULL);
                                } else {
                                        p_mout("Command line option [", mess_w, 
                                               NULL, "\033[93m");
                                        printf("%s", 1[argv]);
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

        exit(P_SUCCESS);
}

