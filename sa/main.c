/*
   (C) 2026, S-Patriarch
   sa - утилита анализа сигнатуры файла.
*/

#include <ph.h>
#include <plc/plc.h>

#include "sa.h"

#include "read-file-bytes.c"
#include "sig-match.c"

int
main(int argc, char *argv[])
{
        if (argc != 2) 
                p_error_quit("Usage: sa [file]\nsa 1.0.0 - file signature analyzer.");

        unsigned char buf[COLS] = {0};
        unsigned char const matrix[ROWS][COLS] = {
                {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a}, /* PNG  */
                {0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46}  /* JPG  */
        };
        char const *tf[] = {
                "PNG", "JPG"
        };
        char *tf_res = NULL;

        if (!read_file_bytes(argv[1], &buf))
                p_error_sys("E");

        if (!sig_match(&buf, &matrix, tf, &tf_res))
                p_error_quit("The file type of %s is undefined.", argv[1]);

        printf("The file %s is a %s file.\n", argv[1], tf_res);

        exit(P_EXIT_SUCCESS);
}

