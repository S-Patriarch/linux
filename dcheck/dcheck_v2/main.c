/* 
   (C) 2025, S-Patriarch
   DomainChecker - проверка доступности и отзывчивости доменов.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <plc/plc.h>
#include "dcheck.h"

int main(int argc, char **argv)
{
        const char *str_err1 = "Failed to allocate memory, strdup().\n";
        const char *str_err2 = "Cannot open file to read.\n";
        const char *str_err3 = "Error fseek.\n";
        
        const char *attr_f = "\033[93m";

        char s_ok[] = "[  \033[32mOK\033[0m  ]";
        char s_fl[] = "[\033[31mFAILED\033[0m]";

        char *file_list = NULL;

        p_clrscr();
        dch_logo();

        switch (argc) {
        case 2:
                file_list = strdup(argv[1]);
                if (file_list == NULL) {
                        p_mout(str_err1, mess_e, NULL, attr_f);
                        exit(P_FAILURE);
                }

                FILE *fi;

                fi = fopen(file_list, "r");
                if (fi == NULL) {
                        p_mout(str_err2, mess_e, NULL, attr_f);
                        exit(P_FAILURE);
                }
                if (fseek(fi, 0, SEEK_SET) != 0) {
                        p_mout(str_err3, mess_e, NULL, attr_f);
                        fclose(fi);
                        exit(P_FAILURE);
                }

                char buf[256];
                char str_out[30];

                while (fgets(buf, sizeof(buf), fi) != NULL) {
                        if (buf[0] == '\0' || buf[0] == '\n')
                                continue;
                        else {
                                bool res_check = dch_domain_checker(buf);
                                if (res_check) {
                                        p_strcpy(str_out, s_ok, sizeof(s_ok));
                                } else {
                                        p_strcpy(str_out, s_fl, sizeof(s_fl));
                                }

                                printf("%s %s\n", str_out, buf);
                        }
                }

                fclose(fi);
                break;
        default:
                dch_help();
                break;
        }

        exit(P_SUCCESS);
}

