//
// (c) 2024 S-Patriarch
// Эхо-клиент.
//
#include "tcpip.hh"
//------------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>
#include <cstring>
#include <cstdlib>
//------------------------------------------------------------------------------
using SA = struct sockaddr;
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
   std::vector<std::string> args(argv,argv+argc);
   if (args.size()!=2) std::cerr << "W: Usage: a.out <IPaddress>\n";
   else {
      try {
         pl::TCPip            tcp;
         struct sockaddr_in   addr;

         std::int32_t sockfd = tcp.tcp_socket(AF_INET,SOCK_STREAM,0);

         std::memset(&addr,0,sizeof(addr));
         addr.sin_family = AF_INET;
         addr.sin_port = htons(pl::mr::SERV_PORT);
         std::string s = args.at(1);
         if (inet_pton(AF_INET,s.c_str(),&addr.sin_addr)<=0) {
            std::cout << "E: inet_pton error for " << s << '\n';
            return 0;
         }

         tcp.tcp_connect(sockfd,(SA*)&addr,sizeof(addr));

         std::int32_t n {};
         char recvline[pl::mr::MAXLINE];
         char sendline[pl::mr::MAXLINE];
         std::memset(&recvline[0],0,sizeof(recvline));
         std::memset(&sendline[0],0,sizeof(sendline));

         while (fgets(sendline,pl::mr::MAXLINE,stdin)!=NULL) {
            tcp.tcp_write(sockfd,sendline,std::strlen(sendline));
            if ((n = tcp.tcp_read(sockfd,recvline,pl::mr::MAXLINE))==0) 
               throw pl::Exception("E: Server terminated prematurely.");
            std::cout << recvline;
            std::memset(&recvline[0],0,sizeof(recvline));
            std::memset(&sendline[0],0,sizeof(sendline));
         }
      }
      catch (std::exception& ex) {
         std::cout << ex.what() << '\n';
      }
   }
   return 0;
}

