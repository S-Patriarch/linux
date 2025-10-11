/*
 * Работа функции:
 * 1. Получение информации об адресе:
 *    Используется функция getaddrinfo для получения структуры addrinfo,
 *    содержащей информацию об адресе домена. В структуре могут содержаться
 *    несколько возможных вариантов адреса (например, для IPv4 и IPv6).
 * 2. Создание сокета:
 *    Создаётся сокет с помощью функции socket.
 *    Сокет может поддерживать как IPv4, так и IPv6.
 * 3. Установка таймаутов:
 *    Устанавливаются таймауты на отправку и получение данных с
 *    помощью функции setsockopt. Это предотвращает бесконечное ожидание
 *    ответа от сервера.
 * 4. Попытка подключения:
 *    Пробуем подключиться к каждому адресу из списка, полученного
 *    функцией getaddrinfo, используя функцию connect.
 * 5. Закрытие сокетов:
 *    После каждой попытки подключения сокеты закрываются с помощью
 *    функции close.
 * 6. Освобождение памяти:
 *    Освобождаем выделенную память для структуры addrinfo с помощью
 *    функции freeaddrinfo.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "dcheck.h"

bool dch_domain_checker(char *host_name) 
{
        host_name[strlen(host_name)-1] = '\0';

        bool connected = false;
        const char *s_port = "80";

        // получаем информацию об адресе хоста
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;     // поддерживаем IPv4 и IPv6
        hints.ai_socktype = SOCK_STREAM; // используем TCP

        struct addrinfo *result;
        int error_code = getaddrinfo((const char *)host_name, s_port, &hints, &result);
        if (error_code < 0) {
                connected = false;
                return connected;
        }

        for (struct addrinfo *res=result; res!=NULL && !connected; res=res->ai_next) {
            // создаем сокет
            int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
            if (sockfd < 0) {
                connected = false;
                return connected;
            }

            // устанавливаем таймауты
            struct timeval tv;
            tv.tv_sec = 5;
            tv.tv_usec = 0;
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
            setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

            // пытаемся подключиться
            if (connect(sockfd, res->ai_addr, res->ai_addrlen) >= 0) {
                connected = true;
            }

            close(sockfd);
        }

        freeaddrinfo(result);
        return connected;
}

