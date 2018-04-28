#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//I'm not sure if I need these at all
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define BUFSIZE 1300
#define PORT_NO 2001

int main(int argc, char *argv[] ){

  char buffer[BUFSIZE];
  char server_message[BUFSIZE] = "Welcome to the server!";
  int message;

  //specify the server adress
  struct sockaddr_in server_adress;
  struct sockaddr_in client;
  server_adress.sin_family = AF_INET;
  server_adress.sin_port = htons(PORT_NO);
  server_adress.sin_addr.s_addr = INADDR_ANY;

  //create a server socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
     fprintf(stderr, "Can't create to the socket\n");
     exit(1);
  }

  //UI
  printf("Server initialized on port %i\n",PORT_NO);

  //bind the socket to our specified IP and port
  bind(server_socket, (struct sockaddr *) &server_adress, sizeof(server_adress));
  if (server_socket < 0) {
     fprintf(stderr, "Can't bind to the socket\n");
     exit(2);
  }
  listen(server_socket, 10);
  if (server_socket < 0) {
     fprintf(stderr, "Can't listen to the socket\n");
     exit(3);
  }

  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);
  if (server_socket < 0) {
     fprintf(stderr, "Can't accept socket\n");
     exit(4);
  }

  //send the greating message
  send(client_socket, server_message, sizeof(server_message), 0);
  printf("Message sent to client\n"); //UI

  //Chatting starts here
  char client_response[BUFSIZE];
  while(1){

    //Recive greating message from the client
    recv(client_socket, &client_response, sizeof(client_response), 0);

    //print out the client response
    printf("The client sent the following message:\n%s\n", client_response);

    //Server's message
    printf("Your message: "); //UI
    fgets(buffer,BUFSIZE,stdin); //Get input from standard input

    //Send a message
    message = send(client_socket, buffer, BUFSIZE, 0);
    if(message < 0) {
       fprintf(stderr, "Can't send message\n");
       return 3;
    }

  }

  //close socket
  close(server_socket);
  close(client_socket);

  return 0;
}
