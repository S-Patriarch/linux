/* 
   (C) 2025-2026, S-Patriarch
   DomainChecker - проверка доступности и отзывчивости доменов.
 */

#include <ph.h>
#include <plc/plc.h>
#include "version.h"
#include "dcheck.h"

#include "logo.c"
#include "help.c"
#include "check-domain.c"

int
main(int argc, char *argv[])
{
        unsigned char   res_check = 0;
        char            *file_list = NULL;
        char            s_ok[] = "[  \033[32mOK\033[0m  ]";
        char            s_fl[] = "[\033[31mFAILED\033[0m]";
        char            buf[256];
        char            str_out[30];
        FILE            *fi = NULL;

        p_clrscr();
        logo();
        putchar((int)'\n');

        if (argc == 2) {
                if ((file_list = strdup(argv[1])) == NULL)
                        p_error_quit("E: Failed to allocate memory, strdup\n");

                if ((fi = fopen(file_list, "r")) == NULL)
                        p_error_quit("E: Cannot open file %s to read\n", argv[1]);

                if (fseek(fi, 0, SEEK_SET) != 0) {
                        fclose(fi);
                        p_error_quit("E: Error fseek\n");
                }

                while (fgets(buf, sizeof(buf), fi) != NULL) {
                        if (buf[0] == '\0' || buf[0] == '\n') {
                                continue;
                        } else {
                                if (!(res_check = check_domain(buf)))
                                        p_strcpy(str_out, s_fl);
                                else
                                        p_strcpy(str_out, s_ok);

                                printf("%s %s\n", str_out, buf);
                        }
                }

                fclose(fi);
                putchar((int)'\n');
        } else {
                help();
                putchar((int)'\n');
        }

        exit(P_EXIT_SUCCESS);
}
