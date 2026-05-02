#ifndef UPD_H
#define UPD_H   3

struct upd_s {
        char upd_pm[10];
};

extern void upd_logo (void) P_NOEXCEPT;
extern void upd_help (void) P_NOEXCEPT;

extern int  upd_detect_package_manager (struct upd_s *upd) P_NOEXCEPT;
extern void upd_command_system (struct upd_s *upd, const char *arg) P_NOEXCEPT;

#endif
