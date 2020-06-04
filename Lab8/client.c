
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>

#define PORT 9037
#define MAXLINE 1023
#define SA struct sockaddr

int m2ain() {
  char buff[MAXLINE + 1];
  int sockfd, maxfd;
  fd_set all_set, rset; //дескрипторы для select
  struct sockaddr_in servaddr, cli;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { //создаем сокет
    printf("Socket creation failed...\n");
    exit(EXIT_FAILURE);
  }
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);

  if ((connect(sockfd, (SA *)&servaddr, sizeof(servaddr))) == -1) { //Устанавливает соединение с сервером.
    printf("Connection with the server failed...\n");
    exit(EXIT_FAILURE);
  }

  maxfd = sockfd + 1;
  FD_ZERO(&all_set);
  FD_SET(STDIN_FILENO, &all_set); //добавляем сокет на stdin
  FD_SET(sockfd, &all_set); //добавляем сокет на сосединенеи с сервером
  struct timeval tv; tv.tv_sec = 2; tv.tv_usec = 0;

  puts("Enter message: ");
  while (1){
    rset = all_set;
    select(maxfd, &rset, NULL, NULL, &tv); //используем для отслеживания нескольких сокетов

    if(FD_ISSET(STDIN_FILENO, &rset)){ //если текущий сокет - stdin
      bzero(buff, sizeof(buff));
      int bytes = read(STDIN_FILENO, buff, MAXLINE); //считываем введенное пользователем
      buff[bytes - 1] = '\0';
      if(send(sockfd, buff, bytes + 1, 0) < 0)//отправляем на сервер
      {
        perror("Client send failed");
        exit(EXIT_FAILURE);
      }
    }

    if(FD_ISSET(sockfd, &rset)){
      bzero(buff, sizeof(buff));
      if(recv(sockfd, buff, MAXLINE + 1, 0) < 0){ //получаем данные с сервера
        perror("Client recv failed");
        exit(EXIT_FAILURE);
      }
      printf("From server: %s\n", buff);
      //buff[0] = '\0';
      puts("Enter message:");
    }
  }
  close(sockfd);
  return EXIT_SUCCESS;
}