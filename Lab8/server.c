
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 9037
#define SA struct sockaddr
#define MAXLINE 1024

int master_socket = 0; //основной сокет
int is_running = 1;

char * open_file(char* filename){
  int fd;
  char * buff;
  struct stat st;
  fd = open(filename, O_RDONLY);

  stat(filename, &st);
  buff = (char*)malloc(st.st_size * sizeof(char));
  if(fd < 0){
    perror("Can`t open file");
    return "Error: Can`t open file";
    //exit(EXIT_FAILURE);
  }
  read(fd, buff, st.st_size);

  close(fd);

  return buff;
}

int wait_request(int sockfd) {
  char buff[MAXLINE];
  int bytes;
  char m_time[] = "time";
  char m_read[] = "open";

  bzero(buff, sizeof(buff));
  if ((bytes = recv(sockfd, buff, MAXLINE, 0)) > 0) {  //получаем данные от клиента
    printf("From client: %s\n", buff);

    if (strcmp(m_time, buff) == 0) { //получаем текущее время
      time_t now = time(0);
      char *time_str = ctime(&now);
      char *time_prefix = "Current time: ";
      time_str[strlen(time_str) - 1] = '\0';
      char *str = (char *)malloc(1 + strlen(time_str) + strlen(time_prefix));
      strcpy(str, time_prefix);
      strcpy(str, time_str);

      if (send(sockfd, str, strlen(str), 0) == -1) { //отправляем данные клиенту
        perror("Server send error");
        // exit(EXIT_FAILURE);
      }
      free(str);
      return bytes;
    }

    if(strncmp(m_read, buff, 4) == 0 && strlen(buff) > 7){ //получаем команду open "filename", открываем файл
      char * str = (char*)malloc(1 + strlen(buff) - 2);
      strncpy(str, buff + 6, strlen(buff) - 7);
      char * file_buff = open_file(str);

      if (send(sockfd, file_buff, strlen(file_buff), 0) == -1) { //отправляем результат клиенту
        perror("Server send error");
        // exit(EXIT_FAILURE);
      }
      free(str);
      return bytes;
    }

    if (send(sockfd, buff, bytes, 0) == -1) { //отправляем результат клиенту
      perror("Server send error");
    }
  }

  if (bytes < 0) {
    perror("Server recv error");
  }

  return bytes;
}

void interrupt_signal(int signal) {
  is_running = 0;
  printf("Interrupt received: Server exit.");
  close(master_socket);
  return;
}

int main() {
  signal(SIGINT, interrupt_signal);

  fd_set master; //основной дескриптор
  fd_set allset; // дескриптор для select
  int fdmax;     //текущий максимальный дескриптор
  struct sockaddr_in servaddr, cli;
  socklen_t len;
  int option = 1; //для setsockopt

  int newfd;

  FD_ZERO(&master); //обнуляем дескрипторы
  FD_ZERO(&allset);

  if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) { //создаем сокет
    perror("Socket creation failed\n");
    exit(EXIT_FAILURE);
  }
  if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &option, //ставим флаг, чтобы можно было переиспользовать порт
                 sizeof(option)) != 0) {
    perror("Socket setsockopt failed\n");
    exit(EXIT_FAILURE);
  }

  bzero(&servaddr, sizeof(servaddr)); //сокет для работы с протоколами IP
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);     // Указываем порт сокета

  if ((bind(master_socket, (SA *)&servaddr, sizeof(servaddr))) != 0) {  //Связывает сокет с конкретным адресом.
    perror("Socket bind failed\n");
    exit(EXIT_FAILURE);
  }
  printf("Socket successfully binded..\n");

  if (listen(master_socket, 10) != 0) {  //Подготавливает привязываемый сокет к принятию входящих соединений.
    perror("Listen failed\n");
    exit(EXIT_FAILURE);
  }
  printf("Server listening..\n");

  FD_SET(master_socket, &master); //добавляет master_socket в сет сокетов

  fdmax = master_socket; //устанавливаем крайний сокет

  while (is_running) {
    allset = master; // копируем сет сокетов
    if (select(fdmax + 1, &allset, NULL, NULL, NULL) == -1) { //используем для отслеживания нескольких сокетов
      perror("Server select error\n");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < fdmax + 1; ++i) {
      if (!FD_ISSET(i, &allset)) { //если сокета нет, то пропускаем
        continue;
      }

      if (i == master_socket) {  //Поступил новый запрос на соединение
        len = sizeof(cli);
        if ((newfd = accept(master_socket, (SA *)&cli, &len)) < 0) { //Используется для принятия запроса на установление соединения от удаленного хоста.
          perror("Server accept failed\n");
          exit(EXIT_FAILURE);
        }
        FD_SET(newfd, &master); //добавляем новый сокет в сет
        if (newfd > fdmax) {
          fdmax = newfd;
        }
        printf("New connection , socket fd is %d , ip is : %s , port : %d\n",
               newfd, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
      } else {
        int response_code = wait_request(i); //
        if (response_code > 0) {
          continue;
        }
        if (response_code == 0) {
          printf("Server: socket %d hung up\n", i);
        }
        close(i); // bye!
        FD_CLR(i, &master);
      }
    }
  }
}