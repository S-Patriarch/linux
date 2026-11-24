/*
   (C) 2026, S-Patriarch
   sa - утилита анализа сигнатуры файла.
*/

#include <ph.h>
#include <plc/plc.h>
#include "ver.h"

#define SIG_LEN  35 /* количество сигнатур в структуре данных  */
#define BUF_LEN  16 /* количество байт считывания  */
#define TYP_LEN  32 /* размер названия типа файла  */

struct sig_s {
        char          type[TYP_LEN]; /* название типа файла  */
        unsigned char buf[BUF_LEN];  /* буфер сигнатуры файла  */
        size_t        len;           /* размер сигнатуры файла */
};

static struct sig_s sig[SIG_LEN] = {
        { "PNG", {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A}, 8 },
        { "JPG (APP0, JFIF)", {0xFF,0xD8,0xFF,0xE0}, 4 },
        { "JPG (APP1, Exif)", {0xFF,0xD8,0xFF,0xE1}, 4 },
        { "JP2 (JPEG 2000)", {0x00,0x00,0x00,0x0C,0x6A,0x50,0x20,0x20,0x0D,0x0A,0x87,0x0A}, 12 },
        { "JXL (JPEG XL Raw Codestream)", {0xFF,0x0A}, 2 },
        { "JXL (JPEG XL ISOBMFF)", {0x00,0x00,0x00,0x0C,0x4A,0x58,0x4C,0x20,0x0D,0x0A,0x87,0x0A}, 12 },
        { "BMP", {0x42,0x4D}, 2 },
        { "TIFF (Intel, little-endian)", {0x49,0x49,0x2A,0x00}, 4 },
        { "TIFF (Motorola, big-endian)", {0x4D,0x4D,0x00,0x2A}, 4 },
        { "GIF (GIF87a)", {0x47,0x49,0x46,0x38,0x37,0x61}, 6 },
        { "GIF (GIF89a)", {0x47,0x49,0x46,0x38,0x39,0x61}, 6 },
        { "QOI (Quite OK Image)", {0x71,0x6F,0x69,0x66}, 4 },
        { "ICO (Microsoft Windows Icon)", {0x00,0x00,0x01,0x00}, 4 },
        { "CUR (Microsoft Windows Cursor)", {0x00,0x00,0x02,0x00}, 4 },
        { "ICNS (MacOS X)", {0x00,0x00,0x02,0x00}, 4 },
        { "EXE", {0x4D,0x5A}, 2 },
        { "PDF", {0x25,0x50,0x44,0x46,0x2D}, 5 },
        { "RTF", {0x7B,0x5C,0x72,0x74,0x66}, 5 },
        { "ZIP", {0x50,0x4B,0x03,0x04}, 4 },
        { "DOC (Microsoft Word 97-2003)", {0xD0,0xCF,0x11,0xE0,0xA1,0xB1,0x1A,0xE1}, 8 },
        { "DDS (DirectDraw Surface)", {0x44,0x44,0x53,0x20}, 4 },
        { "EPS (DOS EPS Binary Header)", {0xC5,0xD0,0xD3,0xC6}, 4 },
        { "EPS", {0x25,0x21,0x50,0x53,0x2D,0x41,0x64,0x6F,0x62,0x65,0x2D}, 11 },
        { "EXR (OpenEXR)", {0x76,0x2F,0x31,0x01}, 4 },
        { "PIC (Softimage)", {0x53,0x80,0xF6,0x34}, 4 },
        { "PBM (Plain)", {0x50,0x31}, 2 },
        { "PBM (Raw)", {0x50,0x34}, 2 },
        { "PGM (Plain)", {0x50,0x32}, 2 },
        { "PGM (Raw)", {0x50,0x35}, 2 },
        { "PPM (Plain)", {0x50,0x33}, 2 },
        { "PPM (Raw)", {0x50,0x36}, 2 },
        { "RGB", {0x01,0xDA}, 2 },
        { "XPM (X PixMap)", {0x2F,0x2A,0x20,0x58,0x50,0x4D,0x20,0x2A,0x2F}, 9 },
        { "SH (shell-script)", {0x23,0x21}, 2 },
        { "SWP (swap-file Vim)", {0x62,0x30,0x56,0x49,0x4D}, 5 }
};

static unsigned char buf[BUF_LEN] = {0};

static unsigned char read_file_bytes (char const *) P_NOEXCEPT;
static unsigned char sig_match (char **) P_NOEXCEPT;

int
main(int argc, char *argv[])
{
        if (argc != 2) 
                p_error_quit("sa %s\n"
                             "Usage: sa [file]\n"
                             "sa - file signature analyzer.", VER_STRING);

        if (!read_file_bytes(argv[1]))
                p_error_sys("\033[01;39mE\033[00m");

        char *tf_res = NULL;
        if (!sig_match(&tf_res))
                p_error_quit("\033[01;39mW\033[00m: The file type of "
                             "\033[01;39m%s\033[00m is undefined.", argv[1]);

        printf("sa: The file \033[01;39m%s\033[00m is a "
               "\033[01;39m%s\033[00m file.\n", argv[1], tf_res);
        
        exit(P_EXIT_SUCCESS);
}

static unsigned char 
read_file_bytes(char const *patch) P_NOEXCEPT
{
        P_CLEANUP(p_fclose) FILE *fp = NULL;
        size_t n = 0;

        if ((fp = fopen(patch, "rb")) == NULL)
                return(P_FALSE);

        n = fread(buf, 1, BUF_LEN, fp);

        if (n != BUF_LEN)
                return(P_FALSE);

        return(P_TRUE);
}

static unsigned char 
sig_match(char **tf_res) P_NOEXCEPT
{
        size_t i = 0;

        for (; i < SIG_LEN; i++) {
                if (memcmp(buf, sig[i].buf, sig[i].len) == 0) {
                        *tf_res = sig[i].type;
                        return(P_TRUE);
                }
        }

        return(P_FALSE);
}

