#ifndef __DS_H
#define __DS_H  3

P_BEGIN_DECLS

/* Структура для хранения статистики.  */
struct ds_s {
        long long ds_total_size;    /* общий размер в байтах  */
        long long ds_file_count;    /* количество файлов  */
        long long ds_dir_count;     /* количество директорий  */
        long long ds_symlink_count; /* количество символических ссылок  */
        long long ds_other_count;   /* другие объекты  */      
};

extern void logo (void) P_NOEXCEPT;
extern void help (void) P_NOEXCEPT;

extern int ds_calculate_size_detailed (const char *, const struct stat *, 
                                       int, struct FTW *) P_NOEXCEPT;
extern void ds_fsize (long long) P_NOEXCEPT;
extern void ds_line (const char *, int) P_NOEXCEPT;

P_END_DECLS

#endif /* ds.h  */

