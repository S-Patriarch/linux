CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O3
TARGET = dcheck
SOURCES = main.c logo.c help.c domain_checker.c
OBJS = $(SOURCES:.c=.o)

LIB_NAME = plc
LDFLAGS = -l$(LIB_NAME)

all:	$(TARGET)

# Сборка исполняемого файла
$(TARGET):	$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	@echo "Сборка $(TARGET) завершена"

# Правило для компиляции объектных файлов
%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS)
	@echo "Очистка завершена"

# Пересборка
rebuild:	clean all

.PHONY:	all clean rebuild
