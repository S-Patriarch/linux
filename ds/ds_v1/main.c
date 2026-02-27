/*
   (C) 2026, S-Patriarch
   ds - утилита командной строки для вычисления размера директории.
*/

#define _XOPEN_SOURCE 500 /* обязательно для nftw  */

#include <ph.h>
#include <plc/plc.h>
#include "ds.h"

ds_s    stats = {0, 0, 0, 0, 0};

#include "ds-logo.c"
#include "ds-help.c"
#include "ds-csd.c"
#include "ds-fsize.c"

int
main(int argc, char *argv[]) 
{
        const char     *dir_path;     /* путь к директории  */
        int             result;       /* результат обхода директории  */
        int             flags;        /* битовая маска, управляющая поведением обхода  */
        int             max_open_fd;  /* максимальное количество одновременно открытых 
                                         файловых дескрипторов  */
        struct stat     path_stat;

        /* Проверка аргументов командной строки.  */
        if (argc != 2) {
                p_clrscr();
                ds_logo();
                putchar((int)'\n');
                ds_help();
                putchar((int)'\n');
                exit(1);
        }

        dir_path = argv[1];
        max_open_fd = 64;
        flags = FTW_PHYS | FTW_DEPTH; /* Флаги:
                                       * FTW_PHYS  - не следовать по символьным ссылкам
                                       * FTW_DEPTH - выполнять обход в глубину
                                       */
        p_clrscr();
        ds_logo();
        putchar((int)'\n');

        /* Проверка существования.  */
        if (stat(dir_path, &path_stat) != 0) 
                p_err_quit("E: there is no access to the path\n");

        if (!S_ISDIR(path_stat.st_mode))
                p_err_quit("E: %s is not a directory\n", dir_path);

        printf("Directory      : %s\n", dir_path);
        p_cout("Mode           : FTW_PHYS | FTW_DEPTH\n");
        p_cout("=============================================\n");

        p_start_timer();

        /* Обход дерева.  */
        result = nftw(dir_path, ds_calculate_size_detailed, max_open_fd, flags);

        if (result != 0) { 
                if (result == -1)
                        p_err_quit("E: error while traversing the directory\n");
                else
                        p_err_quit("E: error while traversing the directory (code: %d)\n", result);
        }

        p_stop_timer();

        /* Вывод статистики.  */
        p_cout("Statistics\n");
        p_cout("---------------------------------------------\n");
        printf("Files          : %lld\n", stats.ds_file_count);
        printf("Directories    : %lld\n", stats.ds_dir_count);
        printf("Symbolic links : %lld\n", stats.ds_symlink_count);
        printf("Other objects  : %lld\n", stats.ds_other_count);
        p_cout("---------------------------------------------\n");
        printf("Time spent     : %.0f sec\n", p_duration_seconds());
        ds_fsize(stats.ds_total_size);
        putchar((int)'\n');

        exit(0);
}

