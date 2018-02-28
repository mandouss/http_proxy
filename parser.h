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
#include <vector>
#endif /* parser_hpp */
//using namespace std
class requestHead {
 private:
  std::string method;
  std::string path;
  std::string protocol;
  std::string host;
  std::string head;
  std::string port;
 public:
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
  std::string get_head() {
    return head;
  }std::string get_port() {
    return port;
  }
 
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
  //<<<<<<< HEAD
  std::string length;
  std::string cache;
  std::string expire;
  std::string age;
  std::string etag;
  std::string head;
  std::vector<char> body;
  //=======
  //  std::vector<char> body;
  //>>>>>>> dcde491c3d87f492bf8ec085e36ab371fe559990
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
  std::string get_length() {
    return length;
  }
  std::string get_cache() {
    return cache;
  }
  std::string get_expire() {
    return expire;
  }
  std::string get_age() {
    return age;
  }
  std::string get_etag() {
    return etag;
  }
  std::string get_head() {
    return head;
  }
  std::vector<char> get_body() {
    return body;
  }
  bool parseResponse(char* buff);
  //set_body();
};
