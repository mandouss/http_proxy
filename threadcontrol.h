#ifndef _THREADCONTROL_H__
#define _THREADCONTROL_H__
#define buff_size 104800
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


class thread_control {
 public:
  int sockfd_t; //thread's sockfd for browers
  struct addrinfo * host_info_list_t;
  thread_control(int s, struct addrinfo * hilt): sockfd_t(s), host_info_list_t(hilt) {}
  ~thread_control(){}
};


class proxy_control{
 private:
  int sockfd; //for browser
  struct addrinfo *host_info_list; //proxy
  char buff[buff_size]; 
  int uid;
  //class req_str()  Xiaoyu
  //{ char * hostname;
  //} char * por
 public:
 proxy_control(int s, struct addrinfo * hil): sockfd(s), host_info_list(hil){} //initialize req_str}
  ~proxy_control() {}
  int get_socket() const{
    return sockfd;
  }
  //int send(std::string);
  //int recv(std::string); 
};

#endif
