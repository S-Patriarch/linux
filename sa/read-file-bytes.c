unsigned char 
read_file_bytes(char const *patch, unsigned char (*buf)[COLS]) P_NOEXCEPT
{
        P_CLEANUP(p_fclose) FILE *fp = NULL;
        size_t n = 0;

        if ((fp = fopen(patch, "rb")) == NULL)
                return(P_FALSE);

        n = fread(*buf, 1, COLS, fp);

        if (n != COLS)
                return(P_FALSE);

        return(P_TRUE);
}

