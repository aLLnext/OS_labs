//
// Created by sapiest on 27.05.2020.
//

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <zconf.h>

#define PORT 8080
#define SA struct sockaddr
#define MAXLINE 1024

void wait_request(int sockfd) {
  char buff[MAXLINE];
  int n;

  while (1) {
    bzero(buff, sizeof(buff));

    read(sockfd, buff, sizeof(buff));
    if(strncmp("time", buff, 4) == 0){
      printf("Current time.\n");
    }else {
      printf("From client: %s\n To client : ", buff);
    }
    bzero(buff, sizeof(buff));

    n = 0;
    while ((buff[n++] = getchar()) != '\n');
    write(sockfd, buff, sizeof(buff));



    if (strncmp("exit", buff, 4) == 0) {
      printf("Server exit.\n");
      break;
    }
  }
}

int main() {
  //дескрипторы и длина
  int sockfd, connfd, updfd, nready, maxfdp1;
  char buffer[MAXLINE];
  pid_t childpid;
  fd_set rset;
  ssize_t n;
  socklen_t len;
  const int on = 1;
  struct sockaddr_in servaddr, cli;


  //создаем сокет
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "Socket creation failed\n");

    return EXIT_FAILURE;
  }
  printf("Socket successfully created..\n");

  //обнуляем (n bytes = 0 в servaddr)
  bzero(&servaddr, sizeof(servaddr));

  // задаем IP и порт
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
    fprintf(stderr, "Socket bind failed\n");

    return EXIT_FAILURE;
  }
  printf("Socket successfully binded..\n");

  if (listen(sockfd, 10) != 0) {
    fprintf(stderr, "Listen failed\n");

    return EXIT_FAILURE;
  }
  printf("Server listening..\n");

  FD_ZERO(&rset);

  while (1){
    FD_SET(sockfd, &rset);

    nready = select(sockfd +1, &rset, NULL, NULL, NULL);
    if(FD_ISSET(sockfd, &rset)){
      len = sizeof(cli);

      if ((connfd = accept(sockfd, (SA *)&cli, &len)) < 0) {
        fprintf(stderr, "Server accept failed\n");

        return EXIT_FAILURE;
      }
      printf("server acccept the client...\n");

      if((childpid = fork()) == 0){
        close(sockfd);
        wait_request(connfd);
      }

      close(connfd);
    }
  }


  return EXIT_SUCCESS;
}