/* 
   Copyright (C) 2026, S-Patriarch
   pmkdir - безопасная и простая реализация mkdir.
*/

#include <ph.h>

int
main(int argc, char *argv[])
{
        if (argc <= 1) {
                printf("Usage: pmkdir [name]\n");
                exit(0);
        }

        if (mkdir(argv[1], 0777) == 0)
                exit(0);

        switch (errno) {
        case EACCES:
                fprintf(stderr, "pmkdir: invalid permission to create folder\n");
                break;
        case EDQUOT:
                fprintf(stderr, "pmkdir: exceeded max disk blocks or inodes on the filesystem\n");
                break;
        case EEXIST:
                fprintf(stderr, "pmkdir: path [%s] already exists\n", argv[1]);
                break;
        case EFAULT:
                fprintf(stderr, "pmkdir: path points outside of accessible address space\n");
                break;
        case EINVAL:
                fprintf(stderr, "pmkdir: invalid directory name: [%s]\n", argv[1]);
                break;
        case ELOOP:
                fprintf(stderr, "pmkdir: to many symbolic links encountered when resolving [%s]. Possible loop\n", argv[1]);
                break;
        case EMLINK:
                fprintf(stderr, "pmkdir: number of links in parrent directory exceeds LINK_MAX\n");
                break;
        case ENAMETOOLONG:
                fprintf(stderr, "pmkdir: directory name to long: [%s]\n", argv[1]);
                break;
        case ENOENT:
                fprintf(stderr, "pmkdir: a parent of the path: [%s] could not be found\n", argv[1]);
                break;
        case ENOMEM:
                fprintf(stderr, "pmkdir: insufficient kernel memory\n");
                break;
        case ENOSPC:
                fprintf(stderr, "pmkdir: insufficient space left on disk\n");
                break;
        case ENOTDIR:
                fprintf(stderr, "pmkdir: a component used in path: [%s] is not a directory\n", argv[1]);
                break;
        case EPERM:
                fprintf(stderr, "pmkdir: the filesystem does not support the creation of directories\n");
                break;
        case EROFS:
                fprintf(stderr, "pmkdir: the filesystem is read-only\n");
                break;
        case EOVERFLOW:
                fprintf(stderr, "pmkdir: UID or GID mappings have not been configured\n");
                break;
        }

        exit(1);
}

