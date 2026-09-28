/*
 * (C) 2026, S-Patriarch
 * ds - утилита командной строки для вычисления размера директории.
 */

#define _XOPEN_SOURCE 500 /* обязательно для nftw  */

#include <ph.h>
#include <plc/plc.h>
#include "ds.h"
#include "version.h"

struct ds_s stats = {0, 0, 0, 0, 0};

#include "logo.c"
#include "help.c"
#include "ds-csd.c"
#include "ds-fsize.c"
#include "ds-line.c"

int
main(int argc, char *argv[]) 
{
        const char  *s1 = NULL, *s2 = NULL;
        const char  *dir_path = NULL; /* путь к директории  */
        int         res;              /* результат обхода директории  */
        int         flags;            /* битовая маска, управляющая поведением обхода  */
        int         max_open_fd;      /* максимальное количество одновременно открытых 
                                         файловых дескрипторов  */
        struct stat path_stat;

        /* Проверка аргументов командной строки.  */
        if (argc != 2) {
                p_clrscr();
                logo();
                putchar((int)'\n');
                help();
                putchar((int)'\n');
                exit(P_EXIT_FAILURE);
        }

        s1 = "\u2500";
        s2 = "\u2550";
        dir_path = argv[1];
        max_open_fd = 64;
        flags = FTW_PHYS | FTW_DEPTH; /* Флаги:
                                         FTW_PHYS  - не следовать по символьным ссылкам
                                         FTW_DEPTH - выполнять обход в глубину  */
        
        p_clrscr();
        logo();
        putchar((int)'\n');

        /* Проверка существования.  */
        if (stat(dir_path, &path_stat) != 0) 
                p_error_quit("E: There is no access to the path\n");

        if (!S_ISDIR(path_stat.st_mode))
                p_error_quit("E: %s is not a directory\n", dir_path);

        printf("Directory      : %s\n", dir_path);
        printf("Mode           : FTW_PHYS | FTW_DEPTH\n");
        ds_line(s2, 45);
        putchar((int)'\n');

        /* Обход дерева.  */
        printf("Scanning...");
        fflush(stdout);

        p_timer_start();
        res = nftw(dir_path, ds_calculate_size_detailed, max_open_fd, flags);
        p_timer_stop();

        if (res != 0) { 
                if (res == -1) 
                        p_error_quit("E: Error while traversing the directory\n");
                else
                        p_error_quit("E: Error while traversing the directory (code: %d)\n", res);
        }

        /* Вывод статистики.  */
        putchar((int)'\r');
        printf("Statistics \n");
        ds_line(s1, 45);
        putchar((int)'\n');
        printf("Files          : %lld\n", stats.ds_file_count);
        printf("Directories    : %lld\n", stats.ds_dir_count);
        printf("Symbolic links : %lld\n", stats.ds_symlink_count);
        printf("Other objects  : %lld\n", stats.ds_other_count);
        ds_line(s1, 45);
        putchar((int)'\n');
        printf("Time spent     : %.0f sec\n", p_duration_seconds());
        ds_fsize(stats.ds_total_size);
        putchar((int)'\n');

        exit(P_EXIT_SUCCESS);
}

