//
// (c) 2024 S-Patriarch
// Простой клиент времени и даты.
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
#define PORT   13
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
         addr.sin_port = htons(PORT);
         std::string s = args.at(1);
         if (inet_pton(AF_INET,s.c_str(),&addr.sin_addr)<=0) {
            std::cout << "E: inet_pton error for " << s << '\n';
            return 0;
         }

         tcp.tcp_connect(sockfd,(SA*)&addr,sizeof(addr));

         std::int32_t n {};
         char recvline[pl::mr::MAXLINE+1];
         while ((n = tcp.tcp_read(sockfd,recvline,pl::mr::MAXLINE))>0) {
            recvline[n] = 0; // символ конца строки
            std::cout << recvline;
         }
      }
      catch (std::exception& ex) {
         std::cout << ex.what() << '\n';
      }
   }
   return 0;
}

