#define ROWS 2
#define COLS 8

/* Открывает файл в бинарном режиме и считывает в буфер первые восемь 
   исходных байт. 
   Возвращает: 
   P_TRUE при успехе, 
   P_FALSE при ошибке и коротком файле, размер которого меньше 8 байт.  */
extern unsigned char read_file_bytes (char const *patch, 
                                      unsigned char (*buf)[COLS]) P_NOEXCEPT;

/* Сравнивает буфер, считанный из файла, с сигнатурами файлов на предмет
   совпадения.
   Возвращает: 
   P_TRUE при наличии совпадения, 
   P_FALSE при его отсутствии.  */
extern unsigned char sig_match (unsigned char (*buf)[COLS],
                                unsigned char const (*matrix)[ROWS][COLS],
                                char const *tf[], char **tf_res) P_NOEXCEPT;

