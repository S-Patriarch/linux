#ifndef UPD_H
#define UPD_H   3

typedef struct {
        char  s_pm[10];
} upd_s;

void upd_logo(void);
void upd_help(void);

int upd_detect_package_manager(upd_s *upd);
void upd_command_system(upd_s *upd, const char *arg);

#endif

