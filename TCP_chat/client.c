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

#define BUFSIZE 1301
#define PORT_NO 2001

int main(int argc, char *argv[] ){

  int network_socket;
  char buffer[BUFSIZE];
  char server_addr[16];
  int ip;
  int connection_status;
  int message;
  char server_response[BUFSIZE];

  //specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT_NO);
  server_address.sin_addr.s_addr = INADDR_ANY;

  //create a socket
  network_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (network_socket < 0) {
    fprintf(stderr, "Can't create to the socket\n");
    exit(1);
  }

  //Somehow this makes the first argument the server IP to connect to
  sprintf(server_addr, "%s", argv[1]);
  ip = inet_addr(server_addr);

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
  printf("The server sent the following data:\n%s\n", server_response);

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

    //Recive message from the server
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //print out the server response
    printf("The other client sent the following message:\n%s\n", server_response);

  }

  //close socket
  close(network_socket);
  return 0;
}
