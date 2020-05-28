//
// Created by sapiest on 27.05.2020.
//

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>

#define PORT 8080
#define MAX 80
#define SA struct sockaddr


void send_msg(int sockfd){
  char buff[MAX];
  int n;
  while (1){
    bzero(buff, sizeof(buff));
    printf("Enter the string: ");
    n = 0;
    while ((buff[n++] = getchar())!= '\n');
    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("From server: %s", buff);
    if((strncmp(buff, "exit", 4)) == 0){
      printf("Client exit.\n");
      break;
    }

  }
}

int main() {
  //объявляем дескрипторы
  int sockfd;
  struct sockaddr_in servaddr, cli;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    fprintf(stderr, "Socket creation failed\n");

    return EXIT_FAILURE;
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);

  if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
    fprintf(stderr, "Socket creation failed\n");

    return EXIT_FAILURE;
  }

  send_msg(sockfd);

  close(sockfd);

  return EXIT_SUCCESS;
}