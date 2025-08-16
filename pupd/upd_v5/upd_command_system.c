#include <stdlib.h>
#include <string.h>
#include "upd.h"

void upd_command_system(upd_s *upd, const char *arg) 
{
        if (strcmp(upd->s_pm, "apt") == 0) {
                if ((strcmp(arg, "-f")==0) || (strcmp(arg, "--full")==0)) {
                        system("sudo apt update");
                        system("sudo apt full-upgrade -y");
                        system("sudo apt autoremove -y");
                        system("sudo apt autoclean -y");
                        system("sudo apt clean -y");
                }
                if ((strcmp(arg, "-c")==0) || (strcmp(arg, "--clean")==0)) {
                        system("sudo apt autoremove -y");
                        system("sudo apt autoclean -y");
                        system("sudo apt clean -y");
                }
                if ((strcmp(arg, "-u")==0) || (strcmp(arg, "--update")==0)) {
                        system("sudo apt update");
                        system("sudo apt full-upgrade -y");
                }
        }

        if (strcmp(upd->s_pm, "dnf") == 0) {
                if ((strcmp(arg, "-f")==0) || (strcmp(arg, "--full")==0)) {
                        system("sudo dnf check-update");
                        system("sudo dnf upgrade --refresh -y");
                        system("sudo dnf autoremove -y");
                        system("sudo dnf clean all -y");
                }
                if ((strcmp(arg, "-c")==0) || (strcmp(arg, "--clean")==0)) {
                        system("sudo dnf autoremove -y");
                        system("sudo dnf clean all -y");
                }
                if ((strcmp(arg, "-u")==0) || (strcmp(arg, "--update")==0)) {
                        system("sudo dnf check-update");
                        system("sudo dnf upgrade --refresh -y");
                }
        }
        
        if (strcmp(upd->s_pm, "pacman") == 0) {
                if ((strcmp(arg, "-f")==0) || (strcmp(arg, "--full")==0)) {
                        system("sudo pacman -Syu --noconfirm");
                        system("sudo pacman -Rns --noconfirm");
                        system("sudo pacman -Sc --noconfirm");
                }
                if ((strcmp(arg, "-c")==0) || (strcmp(arg, "--clean")==0)) {
                        system("sudo pacman -Rns --noconfirm");
                        system("sudo pacman -Sc --noconfirm");
                }
                if ((strcmp(arg, "-u")==0) || (strcmp(arg, "--update")==0)) {
                        system("sudo pacman -Syu --noconfirm");
                }
        }
        
        if (strcmp(upd->s_pm, "zypper") == 0) {
                if ((strcmp(arg, "-f")==0) || (strcmp(arg, "--full")==0)) {
                        system("sudo zypper refresh");
                        system("sudo zypper update -y");
                        system("sudo zypper clean --all");
                }
                if ((strcmp(arg, "-c")==0) || (strcmp(arg, "--clean")==0)) {
                        system("sudo zypper clean --all");
                }
                if ((strcmp(arg, "-u")==0) || (strcmp(arg, "--update")==0)) {
                        system("sudo zypper refresh");
                        system("sudo zypper update -y");
                }
        }
}

