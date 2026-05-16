// Copyright (C) 2026, S-Patriarch

int 
upd_detect_package_manager(struct upd_s *upd) P_NOEXCEPT 
{
        int     iret = P_FAILURE;
        FILE    *file = fopen("/etc/os-release", "r");

        if (file == NULL) return(P_FAILURE);

        char line[256];
        while (fgets(line, sizeof(line), file)) {
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
                                (--len)[id_value] = '\0';

                        if (strcmp(id_value, "debian") == 0) {
                                p_strcpy(upd->upd_pm, "apt");
                                iret = P_SUCCESS;
                                goto ret;
                        }
                        if (strcmp(id_value, "ubuntu") == 0) {
                                p_strcpy(upd->upd_pm, "apt");
                                iret = P_SUCCESS;
                                goto ret;
                        }
                        if (strcmp(id_value, "fedora") == 0) {
                                p_strcpy(upd->upd_pm, "dnf");
                                iret = P_SUCCESS;
                                goto ret;
                        }
                        if (strcmp(id_value, "rhel") == 0) {
                                p_strcpy(upd->upd_pm, "dnf");
                                iret = P_SUCCESS;
                                goto ret;
                        }
                        if (strcmp(id_value, "centos") == 0) {
                                p_strcpy(upd->upd_pm, "dnf");
                                iret = P_SUCCESS;
                                goto ret;
                        }
                        if (strcmp(id_value, "arch") == 0) {
                                p_strcpy(upd->upd_pm, "pacman");
                                iret = P_SUCCESS;
                                goto ret;
                        }
                        if (strcmp(id_value, "opensuse") == 0) {
                                p_strcpy(upd->upd_pm, "zypper");
                                iret = P_SUCCESS;
                                goto ret;
                        }
                }
        }
ret:
        fclose(file);
        return(iret);
}

