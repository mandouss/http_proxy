//
//  parser.hpp
//
//
//  Created by xiaoyuli on 2018/2/26.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#endif /* parser_hpp */
//using namespace std
class requestHead {
 private:
  std::string method;
  std::string path;
  std::string protocol;
  std::string host;
  std::string get_method(){
    return method;
  }
  std::string get_path() {
    return path;
  }
  std::string get_protocol() {
    return protocol;
  }
  std::string get_host() {
    return host;
  }
 public:
  requestHead(){}
  ~requestHead(){}
  bool parseRequest(char *buff);
};

//HTTP response
class responseHead{
 private:
  std::string status;
  std::string code;
  std::string date;
 public:
  responseHead(){}
  ~responseHead(){}
  std::string get_status(){
    return status;
  }
  std::string get_code() {
    return code;
  }
  std::string get_date() {
    return date;
  }
  bool parseResponse(char* buff);
};
