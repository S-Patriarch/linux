/* 
 * (C) 2025, S-Patriarch 
 *
 * upd - утилита командной строки.
 * Она предоставляет команды для обновления и очистке системы после обновления.
 * upd работает с такими менеджерами пакетов, как apt, dnf, pacman, zypper.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <plc/plc.h>
#include "upd.h"

int main(int argc, char **argv)
{
        if (argc == 2) {
                upd_s upd;
                int res = upd_detect_package_manager(&upd);

                if (res == P_FAILURE) {
                        p_mout("I can't identify the OS\n\n", mess_w, NULL, "\033[93m");
                } else {
                        if (*upd.s_pm == '\0') {
                                p_mout("The package manager is not known\n\n", mess_w, NULL, "\033[93m");
                        } else {
                                const char *arg = argv[1];

                                if (strcmp(arg, "-f") == 0       || 
                                    strcmp(arg, "-u") == 0       ||
                                    strcmp(arg, "-c") == 0       ||
                                    strcmp(arg, "--full") == 0   ||
                                    strcmp(arg, "--update") == 0 ||
                                    strcmp(arg, "--clean") == 0) {
                                        p_clrscr();
                                        upd_logo();
                                        putchar('\n');
                                        
                                        p_start_timer();
                                        upd_command_system(&upd, arg);
                                        p_stop_timer();
                                        
                                        putchar('\n');
                                        p_mout("Time spent : ", mess_w, NULL, "\033[93m");
                                        printf("%.2f", p_duration_minutes());
                                        p_mout(" minutes\n\n", mess_n, NULL, NULL);
                                } else {
                                        p_mout("Command line option [", mess_w, NULL, "\033[93m");
                                        printf("%s", arg);
                                        p_mout("] unclear\n\n", mess_n, NULL, NULL);
                                }
                        }
                }                        
        } else {
                p_clrscr();
                upd_logo();
                putchar('\n');
                upd_help();
                putchar('\n');
        }

        exit(P_SUCCESS);
}

