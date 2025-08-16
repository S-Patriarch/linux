#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <plc/plcdef.h>
#include <plc/string.h>
#include "upd.h"

int upd_detect_package_manager(upd_s *upd) 
{
        FILE *file = fopen("/etc/os-release", "r");
        if (file == NULL)
                return P_FAILURE;

        char line[256];
        while (fgets(line, sizeof(line), file)) {
                char *id_pos = strstr(line, "ID=");
                if (id_pos != NULL) {
                        // пропускаем ID= и копируем оставшуюся часть строки
                        char *id_value = id_pos + 3;

                        // удаляем возможные кавычки и пробелы в начале
                        while (*id_value == ' ' || *id_value == '"' || *id_value == '\'')
                                id_value++;

                        // убаляем пробелы и кавычки в конце
                        size_t len = strlen(id_value);
                        while (len > 0 && (id_value[len-1] == ' '  || 
                                           id_value[len-1] == '"'  || 
                                           id_value[len-1] == '\'' || 
                                           id_value[len-1] == '\n'))
                                id_value[--len] = '\0';

                        if (strcmp(id_value, "debian") == 0) {
                                fclose(file);
                                p_strcpy(upd->s_pm, "apt", sizeof("apt"));
                                return P_SUCCESS;
                        }
                        if (strcmp(id_value, "ubuntu") == 0) {
                                fclose(file);
                                p_strcpy(upd->s_pm, "apt", sizeof("apt"));
                                return P_SUCCESS;
                        }
                        if (strcmp(id_value, "fedora") == 0) {
                                fclose(file);
                                p_strcpy(upd->s_pm, "dnf", sizeof("dnf"));
                                return P_SUCCESS;
                        }
                        if (strcmp(id_value, "rhel") == 0) {
                                fclose(file);
                                p_strcpy(upd->s_pm, "dnf", sizeof("dnf"));
                                return P_SUCCESS;
                        }
                        if (strcmp(id_value, "centos") == 0) {
                                fclose(file);
                                p_strcpy(upd->s_pm, "dnf", sizeof("dnf"));
                                return P_SUCCESS;
                        }
                        if (strcmp(id_value, "arch") == 0) {
                                fclose(file);
                                p_strcpy(upd->s_pm, "pacman", sizeof("pacman"));
                                return P_SUCCESS;
                        }
                        if (strcmp(id_value, "opensuse") == 0) {
                                fclose(file);
                                p_strcpy(upd->s_pm, "zypper", sizeof("zypper"));
                                return P_SUCCESS;
                        }
                }
        }

        fclose(file);
        return P_FAILURE;
}

