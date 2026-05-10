unsigned char
upd_network_check(void) P_NOEXCEPT 
{
        size_t i, j;
        unsigned char res = P_FALSE;

        const char *port[] = { "443", "80" };
        const char *host[] = { "yandex.ru",
                               "dzen.ru",
                               "mail.ru",
                               "gosuslugi.ru",
                               "rutube.ru" };

        for (i = 0; i < 2 && !res; i++) 
                for (j = 0; j < 5 && !res; j++) 
                        res = p_dcheck(j[host], i[port]);
                
        return (res);
}

