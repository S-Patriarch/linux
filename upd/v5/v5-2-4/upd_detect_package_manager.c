// Copyright (C) 2026, S-Patriarch

int 
upd_detect_package_manager(struct upd_s *upd) P_NOEXCEPT 
{
        int     iret = -1;
        FILE    *f = fopen("/etc/os-release", "r");

        if (f == NULL) 
                return(-1);

        char line[P_BUFSIZ_256];
        while (fgets(line, sizeof(line), f)) {
                char *id_pos = strstr(line, "ID=");
                if (id_pos != NULL) {
                        /* пропускаем ID= и копируем оставшуюся часть строки  */
                        char *id_value = id_pos + 3;

                        /* удаляем возможные кавычки и пробелы в начале  */
                        while (*id_value == ' ' || 
                               *id_value == '"' || 
                               *id_value == '\'')
                                id_value++;

                        /* убаляем пробелы и кавычки в конце  */
                        size_t len = strlen(id_value);
                        while (len > 0 && (id_value[len-1] == ' '  || 
                                           id_value[len-1] == '"'  || 
                                           id_value[len-1] == '\'' || 
                                           id_value[len-1] == '\n'))
                                id_value[--len] = '\0';

                        if (strcmp(id_value, "debian") == 0) {
                                p_strcpy(upd->upd_pm, "apt");
                                iret = 0;
                                goto ret;
                        }
                        if (strcmp(id_value, "ubuntu") == 0) {
                                p_strcpy(upd->upd_pm, "apt");
                                iret = 0;
                                goto ret;
                        }
                        if (strcmp(id_value, "fedora") == 0) {
                                p_strcpy(upd->upd_pm, "dnf");
                                iret = 0;
                                goto ret;
                        }
                        if (strcmp(id_value, "rhel") == 0) {
                                p_strcpy(upd->upd_pm, "dnf");
                                iret = 0;
                                goto ret;
                        }
                        if (strcmp(id_value, "centos") == 0) {
                                p_strcpy(upd->upd_pm, "dnf");
                                iret = 0;
                                goto ret;
                        }
                        if (strcmp(id_value, "arch") == 0) {
                                p_strcpy(upd->upd_pm, "pacman");
                                iret = 0;
                                goto ret;
                        }
                        if (strcmp(id_value, "opensuse") == 0) {
                                p_strcpy(upd->upd_pm, "zypper");
                                iret = 0;
                                goto ret;
                        }
                }
        }

ret:
        p_fclose((FILE **)&f);
        return(iret);
}

