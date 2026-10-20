#include <stdio.h>
#include <ftw.h>
#include "ds.h"

int
ds_calculate_size_detailed(const char *fpath, const struct stat *sb, 
                           int typeflag, struct FTW *ftwbuf) P_NOEXCEPT 
{
        /* Пропускаем, если нет прав доступа.*/
        if (typeflag == FTW_NS) {
                stats.ds_other_count++;
                printf("W: no access: %s\n", fpath);
                return(0);
        }

        switch (typeflag) {
        case FTW_F:     /* обычный файл  */
                stats.ds_file_count++;
                stats.ds_total_size += sb->st_blocks * 512;
                break;

        case FTW_D:     /* директория  */
        case FTW_DP:    /* директория (пост-порядок)  */
                stats.ds_dir_count++;
                break;

        case FTW_SL:    /* символическая ссылка  */
        case FTW_SLN:   /* символическая ссылка, указывающая на несуществующий файл  */
                stats.ds_symlink_count++;
                break;
                
        default:
                stats.ds_other_count++;
                break;
        }

        return(0); /* продолжаем обход  */
}

