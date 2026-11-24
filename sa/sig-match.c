unsigned char 
sig_match(unsigned char (*buf)[COLS],
          unsigned char const (*matrix)[ROWS][COLS],
          char const *tf[], char **tf_res) P_NOEXCEPT
{
        size_t i = 0;
        
        for (; i < ROWS; i++) {
                if (memcmp(*buf, (*matrix)[i], COLS) == 0) {
                        *tf_res = (char *)tf[i];
                        return(P_TRUE);
                }
        }

        return(P_FALSE);
}

