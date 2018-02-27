#include "socket.h"
#include "threadcontrol.h"

proxySocket::proxySocket(): sockfd(-1), new_socket(-1), conn_socket(-1){
  memset(&host_info, 0, sizeof(host_info));
  host_info_list = NULL;
  //memset(&s_addr, 0, sizeof(s_addr));
}

proxySocket::~proxySocket(){}

int proxySocket::get_conn_socket() {
  return conn_socket;
}

int proxySocket::get_new_socket() {
  return new_socket;
}

int proxySocket::get_sockfd() {
  return sockfd;
}

struct addrinfo * proxySocket::get_host_info_list(){
  return host_info_list;
}

void proxySocket::get_host_info(char * port) {
  int status;
  const char *hostname = NULL;
  host_info.ai_family   = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  host_info.ai_flags    = AI_PASSIVE;
  status = getaddrinfo(hostname, port, &host_info, &host_info_list);
  if(status != 0) {
    std::cerr << "Error: fail to analyze ip address for host" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void proxySocket::setupServer(char * port) {
  int optval = 1;
  int back_log = 20;
  int status = -1;
  sockfd = socket(host_info_list -> ai_family,
		  host_info_list -> ai_socktype,
		  host_info_list -> ai_protocol);
  if(sockfd < 0){
    std::cerr << "Error: fail to create a proxy socket for listening!" <<std::endl;
    exit(EXIT_FAILURE);
  }
  if((status = bind(sockfd, host_info_list->ai_addr, host_info_list->ai_addrlen)) < 0) {
    std::cerr << "fail to bind proxy port and socket!" << std::endl;
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));//set socket reuse
  status = -1;
  if((status = listen(sockfd, back_log)) < 0){ // listen
    std::cerr << "fail to bind proxy port and socket!" << std::endl;
    close(sockfd);
    exit(EXIT_FAILURE);
  }
}

void proxySocket::acceptConnect() {
  std::cout << "Waiting for connection on port!" <<std::endl;
  struct sockaddr_storage socket_addr;
  socklen_t socket_addr_len = sizeof(socket_addr);
  new_socket = accept(sockfd, (struct sockaddr *)&socket_addr, &socket_addr_len);
  if(new_socket < 0) {
    std::cerr << "fail to call accept function!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "new_socket:" << new_socket << std::endl << "accept!" << std::endl;
}

void * multiThreadControl(void * arg_list){
  int new_socket_tmp = ((thread_control *)arg_list) -> new_socket_t;
  struct addrinfo *host_info_list_tmp = ((thread_control *)arg_list) -> host_info_list_t;
  proxy_control sc(new_socket_tmp, host_info_list_tmp);
  //std::cout << sc.get_socket() << std::endl;
  close(sc.get_new_socket());
  pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
  int p_port;
  if(argc != 2) {
    std::cerr << "USage: ./socket <port_num>" <<std::endl;
    exit(EXIT_FAILURE);
  }
  p_port = atoi(argv[1]);
  if(p_port < 1024) {
    std::cerr << "Error: Please input a port larger than 1024!" << std::endl;
    exit(EXIT_FAILURE);
  }
  proxySocket p_socket;
  p_socket.get_host_info(argv[1]);
  p_socket.setupServer(argv[1]);
  if(daemon(0, 1) != 0) {
    std::cerr << "Error: fail to create Daemon!" << std::endl;
    exit(EXIT_FAILURE);
  }
  while(1){
    p_socket.acceptConnect();
    thread_control para_list(p_socket.get_new_socket(),p_socket.get_host_info_list());
    pthread_t thread;
    if(pthread_create(&thread, NULL, multiThreadControl, &para_list) != 0) {
      std::cerr << "fail to create thread!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //std::cout << p_socket.get_Sockfd() << std::endl;
  //std::cout << p_socket.get_S_Socket() << std::endl;
}

