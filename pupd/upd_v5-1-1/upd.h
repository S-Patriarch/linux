#ifndef UPD_H
#define UPD_H   3

typedef struct {
        char    s_pm[10];
} upd_s;

void    upd_logo(void) P_NOEXCEPT;
void    upd_help(void) P_NOEXCEPT;

int     upd_detect_package_manager(upd_s *upd) P_NOEXCEPT;
void    upd_command_system(upd_s *upd, const char *arg) P_NOEXCEPT;

#endif

