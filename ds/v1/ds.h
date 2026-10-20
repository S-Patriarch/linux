#ifndef DS_H
#define DS_H    3

#include <plc/plcdef.h>

/* Структура для хранения статистики.  */
typedef struct {
        long long       ds_total_size;    /* общий размер в байтах  */
        long long       ds_file_count;    /* количество файлов  */
        long long       ds_dir_count;     /* количество директорий  */
        long long       ds_symlink_count; /* количество символических ссылок  */
        long long       ds_other_count;   /* другие объекты  */      
} ds_s;

void    ds_logo(void) P_NOEXCEPT;
void    ds_help(void) P_NOEXCEPT;

int     ds_calculate_size_detailed(const char *, const struct stat *, 
                                   int, struct FTW *) P_NOEXCEPT;
void    ds_fsize(long long) P_NOEXCEPT;

#endif /* DS_H  */

