//
// (c) 2024 S-Patriarch
// Patriarch library : tcpip.hh
//
#ifndef PL_TCPIP_HH
#define PL_TCPIP_HH

#ifndef PL_EXCEPT_HH
#include "except.hh"
#endif

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

#include <cerrno>
#include <cstring>

typedef void Sigfunc(int); // для обработчиков сигналов

namespace pl {
   namespace mr {
      constexpr int LISTENQ     = 1024; // максимальное количество клиентских соединений
      constexpr int MAXLINE     = 4096; // максимальная длина текстовой строки
      constexpr int BUFFSIZE    = 8192; // размер буфера для чтения и записи
      constexpr int MAXSOCKADDR = 128;  // максимальный размер структуры адреса сокета
      constexpr int SERV_PORT   = 9877; // клиент-серверы TCP и UDP
   }
   class TCPip {
      // компонентные функции:
      // tcp_socket()  - создание сокета
      // tcp_bind()    - привязка сокета
      // tcp_listen()  - прослушивание подключений
      // tcp_accept()  - прием данных
      // tcp_connect() - установка соединения
      // tcp_close()   - закрытие созданного сокета
      // tcp_recv()    - чтение данных из сокета
      // tcp_send()    - запись данных в сокет      
      // tcp_read()    - чтение данных из потока
      // tcp_write()   - запись данных в поток
      // tcp_fork()    - порождение дочернего процесса
      // tcp_signal()  - обработчик сигналов 
   private:
      void error_ex(const char* str)
      {
         char errmsg[mr::MAXLINE];
         strcpy(errmsg,str);
         char* s = std::strerror(errno);
         throw Exception(strcat(errmsg,s));
      }
      Sigfunc* _signal(int signo, Sigfunc* func)
      {
         struct sigaction act;
         struct sigaction oact;
         
         act.sa_handler = func;
         sigemptyset(&act.sa_mask);
         act.sa_flags = 0;

         if (signo==SIGALRM) {
#ifdef SA_INTERRUPT
            act.sa_flags |= SA_INTERRUPT; // SunOS 4.x
#endif
         }
         else {
#ifdef SA_RESTART
            act.sa_flags |= SA_RESTART; // SVR4, 44BSD
#endif
         }
         if (sigaction(signo,&act,&oact)<0) return SIG_ERR;
         return oact.sa_handler;
      }
   public:
      int tcp_socket(int domain, int type, int protocol)
         // создание сокета
      {
         int   n {};
         if ((n = socket(domain,type,protocol))<0) 
            error_ex("E: Socket error - ");
         return n;
      }
     void tcp_bind(int fd, const struct sockaddr* addr, socklen_t len)
         // привязка сокета
      {
         if (bind(fd,addr,len)<0) 
            error_ex("E: Bind error - ");
      }
      void tcp_listen(int fd, int n)
         // прослушивание подключений
      {
         if (listen(fd,n)<0) 
            error_ex("E: Listen error - ");
      }
      int tcp_accept(int fd, struct sockaddr* addr, socklen_t* len)
         // прием данных
      {
         int   n {};
         if ((n = accept(fd,addr,len))<0) 
            error_ex("E: Accept error - ");
         return n;
      }
      void tcp_connect(int fd, const struct sockaddr* addr, socklen_t len)
         // установка соединения
      {
         if (connect(fd,addr,len)<0) 
            error_ex("E: Connect error - ");
      }
      void tcp_close(int fd)
         // закрытие созданного сокета
      {
         if (close(fd)<0) 
            error_ex("E: Close error - ");
      }
      ssize_t tcp_recv(int fd, void* ptr, size_t nbytes, int flags)
         // чтение данных из сокета
      {
         ssize_t n {};
         if ((n = recv(fd,ptr,nbytes,flags))<0) 
            error_ex("E: Recv error - ");
         return n;
      }
      void tcp_send(int fd, const void* ptr, size_t nbytes, int flags)
         // запись данных в сокет
      {
         if (send(fd,ptr,nbytes,flags)<0) 
            error_ex("E: Send error - ");
      }
      ssize_t tcp_read(int fd, void* ptr, size_t nbytes)
         // чтение данных из потока
      {
         ssize_t n {};
         if ((n = read(fd,ptr,nbytes))<0) 
            error_ex("E: Read error - ");
         return n;
      }
      void tcp_write(int fd, const void* ptr, size_t nbytes)
         // запись данных в поток
      {
         if (write(fd,ptr,nbytes)<0) 
            error_ex("E: Write error - ");
      }
      pid_t tcp_fork()
         // порождение дочернего процесса
      {
         pid_t pid {};
         if ((pid = fork())<0) 
            error_ex("E: Fork error - ");
         return pid;
      }
      Sigfunc* tcp_signal(int signo, Sigfunc* func)
         // обработчик сигналов
      {
         Sigfunc* sigfunc;
         if ((sigfunc = _signal(signo,func))==SIG_ERR)
            error_ex("E: Signal error - ");
         return sigfunc;
      }
   };
}
#endif // PL_TCPIP_HH
