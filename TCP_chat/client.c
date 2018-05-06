/*
This is a program to manage a debate between two clients. The clients can send messages to each
other. When both clients send the message "yes", the debate is closed.
This client program sends and revives responses from the server.

Usage: ./client IP

Made my Attila Fekete in 2018.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFSIZE 1301
#define PORT_NO 2001

int main(int argc, char *argv[] ){

  printf("\e[1;1H\e[2J"); //clears the screen on linux

  int network_socket;
  char buffer[BUFSIZE];
  char server_addr[16];
  int connection_status;
  int message;
  char server_response[BUFSIZE];

  //specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT_NO); //htons converts normal looking port to some C magic
  server_address.sin_addr.s_addr = INADDR_ANY;

  //create a socket
  network_socket = socket(AF_INET, SOCK_STREAM, 0); //(domain, type, protocoll)
  //AF_INET: normal ip adress
  //SOCK_STREAM: Provides sequenced, two-way byte streams that are reliable and connection-oriented
  if (network_socket < 0) {
    fprintf(stderr, "Can't create to the socket\n");
    exit(1);
  }

  //This makes the first argument the server IP to connect to
  sprintf(server_addr, "%s", argv[1]);
  inet_addr(server_addr);

  //Connect to server
  connection_status = connect(network_socket, (struct sockaddr *) &server_address,
                                  sizeof(server_address));

  //Check for error with the connection
  if(connection_status == -1){
    fprintf(stderr, "Can't connect to the socket\n");
    exit(2);
  }

  //Recive greating message from the server
  recv(network_socket, &server_response, sizeof(server_response), 0);

  //print out the server response
  printf("The server sent the following message:\n%s\n", server_response);
  //if this is Client2 it will skip the writing part of the endless loop in the first cycle
  //so it will just print Client1's message
  if (strstr(server_response, "Welcome to the server! You're Client2.") != NULL){
    goto CSECS;
  }

  //Chatting starts here
  while(1){

    //Client's message
    printf("Your message: "); //UI
    fgets(buffer,BUFSIZE,stdin); //Get input from standard input

    //Send a message
    message = send(network_socket, buffer, BUFSIZE, 0);
    if(message < 0) {
       fprintf(stderr, "Can't send message\n");
       exit(3);
    }

    CSECS://goto label
    //Recive message from the server
    recv(network_socket, &server_response, sizeof(server_response), 0);
    //if the server sends "Debate closed" then the program closes
    if (strstr(server_response, "Debate closed") != NULL){
      printf("%s",server_response);
      break;
    }

    //print out the server response
    printf("The other client sent the following message:\n%s\n", server_response);

  }

  //close socket
  close(network_socket);
  return 0;
}
