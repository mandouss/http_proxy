#include "parser.h"
//
//  parser.cpp
//
//
//  Created by xiaoyuli on 2018/2/26.
//

bool requestHead::parseRequest(char* buff){
  //bool ans = false;
  const char *start = buff;
  const char *curr = buff;
  const char *newline = buff;

  while(*curr != ' '){
    curr++;
  }

  method = std::string(start, curr - start);
  start = curr + 1;
  curr = curr + 1;
  while(*curr != ' '){
    curr++;
  }

  path = std::string(start, curr - start);
  start = curr + 1;
  curr = curr + 1;

  size_t colon;
  size_t slash;
  if((colon = path.find(':')) != std::string::npos){
    if((slash = path.find('/', colon)) == std::string::npos){
      port = std::string(path, colon + 1);
    }else{
      port = std::string(path, colon + 1, slash - colon - 1);
    }
  }else{
    port = "80";
  }
  
  while(*newline != '\r'){
    newline++;
  }
  protocol = std::string(start, newline - start);
  head = std::string(buff, newline - buff);

  start = newline + 8;
  newline = newline + 8;
  while(*newline != '\r'){
    newline++;
  }
  host = std::string(start, newline - start);

  std::cout<< "method: "<< method << std::endl;
  std::cout<< "path: " << path << std::endl;
  std::cout<< "protocol: " << protocol << std::endl;
  std::cout<< "host: " << host << std::endl;
  std::cout<< "head: " << head << std::endl;
  std::cout << "port: " << port << std::endl;
  
  return true;
}

/*
bool parseRequest(char* buff, requestHead& head){
  bool ans = false;
  const char *start = buff;
  const char *curr = buff;
  const char *newline = buff;

  while(*curr != ' '){
    curr++;
  }

  head.method = std::string(start, curr - start);
  start = curr + 1;
  curr = curr + 1;
  while(*curr != ' '){
    curr++;
  }

  head.path = std::string(start, curr - start);
  start = curr + 1;
  curr = curr + 1;

  while(*newline != '\r'){
    newline++;
  }
  head.protocol = std::string(start, newline - start);


  start = newline + 2;
  newline = newline + 2;
  while(*newline != '\r'){
    newline++;
  }
  head.host = std::string(start, newline - start);

  std::cout<< "method: "<< head.method << std::endl;
  std::cout<< "path: " << head.path << std::endl;
  std::cout<< "protocol: " << head.protocol << std::endl;
  std::cout<< "host: " << head.host << std::endl;

  return true;
}
*/

bool responseHead::parseResponse(char *buff){
  char* start = buff;
  char* end = strstr(start, "\r\n");
  char* line = end;
  head = std::string(start, line - start);
  start = strchr(start, ' ') + 1;
  end = strchr(start, ' ');
  code = std::string(start, end - start);

  start = strchr(start, ' ') + 1;
  end = strstr(start, "\r\n");
  status = std::string(start, end - start);

  if((start = strstr(line, "\r\nDate: ")) != NULL){
    //std::cout << start;
    start = strchr(start, ' ') + 1;
    end = strstr(start, "\r\n");
    date = std::string(start, end - start);
  }else{
    date = "";
  }
  if((start = strstr(line, "\r\nExpires: ")) != NULL){
    start = strchr(start, ' ') + 1;
    end = strstr(start, "\r\n");
    expire = std::string(start, end - start);
  }else{
    expire = "";
  }

  if((start = strstr(line, "\r\nContent-Length: ")) != NULL){                  \

    start = strchr(start, ' ') + 1;
    end = strstr(start, "\r\n");
    length = std::string(start, end - start);
  }else{
    length = "";
  }
  if((start = strstr(line, "\r\nCache-Control: ")) != NULL){                  \
    start = strchr(start, ' ') + 1;
    end = strstr(start, "\r\n");
    cache = std::string(start, end - start);
  }else{
    cache = "";
  }
  if((start = strstr(line, "\r\nEtag: ")) != NULL){                  \
    start = strchr(start, ' ') + 1;
    end = strstr(start, "\r\n");
    cache = std::string(start, end - start);
  }else{
    cache = "";
  }
  
  std::cout<< "code: "<< code << std::endl;
  std::cout<< "status: " << status << std::endl;
  std::cout<< "date: " << date << std::endl;
  std::cout<< "head: " << head << std::endl;
  return true;
}

int main(){
  char msg1[]= "GET /test:12345/next HTTP/1.1\r\nHost: 192.241.213.46:6880\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
  char msg2[]= "HTTP/1.x 200 OK\r\nTransfer-Encoding: chunked\r\nDate: Sat, 28 Nov 2009 04:36:25 GMT\r\n\r\n";
  requestHead head1;
  head1.parseRequest(msg1);
  responseHead head2;
  head2.parseResponse(msg2);
  return EXIT_SUCCESS;

}
