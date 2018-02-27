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
public:
  std::string method;
  std::string path;
  std::string protocol;
  std::string host;
};
class responseHead{
public:
  std::string status;
  std::string code;
  std::string date;
};

bool parseRequest(char* buff, requestHead& head);
bool parseResponse(char* buff, responseHead& head);
