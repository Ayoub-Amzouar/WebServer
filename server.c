



// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);


    
     char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
    return 0;
}


//------------------------------------------------------------------------------------------------------------
/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/types.h> 
// #include <sys/socket.h>
// #include <netinet/in.h>

// void dostuff(int); /* function prototype */
// void error(const char *msg)
// {
//     perror(msg);
//     exit(1);
// }

// int main(int argc, char *argv[])
// {
//      int sockfd, newsockfd, portno, pid;
//      socklen_t clilen;
//      struct sockaddr_in serv_addr, cli_addr;

//      if (argc < 2) {
//          fprintf(stderr,"ERROR, no port provided\n");
//          exit(1);
//      }
//      sockfd = socket(AF_INET, SOCK_STREAM, 0);
//      if (sockfd < 0) 
//         error("ERROR opening socket");
//      bzero((char *) &serv_addr, sizeof(serv_addr));
//      portno = atoi(argv[1]);
//      serv_addr.sin_family = AF_INET;
//      serv_addr.sin_addr.s_addr = INADDR_ANY;
//      serv_addr.sin_port = htons(portno);
//      if (bind(sockfd, (struct sockaddr *) &serv_addr,
//               sizeof(serv_addr)) < 0) 
//               error("ERROR on binding");
//      listen(sockfd,5);
//      clilen = sizeof(cli_addr);
//      while (1) {
//          newsockfd = accept(sockfd, 
//                (struct sockaddr *) &cli_addr, &clilen);
//          if (newsockfd < 0) 
//              error("ERROR on accept");
//          pid = fork();
//          if (pid < 0)
//              error("ERROR on fork");
//          if (pid == 0)  {
//              close(sockfd);
//              dostuff(newsockfd);
//              exit(0);
//          }
//          else close(newsockfd);
//      } /* end of while */
//      close(sockfd);
//      return 0; /* we never get here */
// }

// /******** DOSTUFF() *********************
//  There is a separate instance of this function 
//  for each connection.  It handles all communication
//  once a connnection has been established.
//  *****************************************/
// void dostuff (int sock)
// {
//    int n;
//    char buffer[256];
      
//    bzero(buffer,256);
//    n = read(sock,buffer,255);
//    if (n < 0) error("ERROR reading from socket");
//    printf("Here is the message: %s\n",buffer);
//    n = write(sock,"I got your message",18);
//    if (n < 0) error("ERROR writing to socket");
// }

//-------------------------------------------------------------------------------------------------------------------------------
// /* a server in the unix domain.  The pathname of 
//    the socket address is passed as an argument */
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/un.h>
// #include <stdio.h>
// void error(const char *);
// int main(int argc, char *argv[])
// {
//    int sockfd, newsockfd, servlen, n;
//    socklen_t clilen;
//    struct sockaddr_un  cli_addr, serv_addr;
//    char buf[80];

//    if ((sockfd = socket(PF_UNIX,SOCK_STREAM,0)) < 0)
//        error("creating socket");
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sun_family = AF_UNIX;
//    strcpy(serv_addr.sun_path, argv[1]);
//    servlen=strlen(serv_addr.sun_path) + 
//                      sizeof(serv_addr.sun_family);
//    if(bind(sockfd,(struct sockaddr *)&serv_addr,servlen)<0)
//        error("binding socket"); 

//    listen(sockfd,5);
//    clilen = sizeof(cli_addr);
//    newsockfd = accept(
//         sockfd,(struct sockaddr *)&cli_addr,&clilen);
//    if (newsockfd < 0) 
//         error("accepting");
//    n=read(newsockfd,buf,80);
//    printf("A connection has been established\n");
//    write(1,buf,n);
//    write(newsockfd,"I got your message\n",19);
//    close(newsockfd);
//    close(sockfd);
//    return 0;
// }

// void error(const char *msg)
// {
//     perror(msg);
//     exit(0);
// }