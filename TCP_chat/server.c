#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//I'm not sure if I need these at all
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define BUFSIZE 1301
#define PORT_NO 2001

int main(int argc, char *argv[] ){

  int server_socket;
  int client_socket;
  int client_socket2;
  char buffer[BUFSIZE];
  char server_message[BUFSIZE] = "Welcome to the server! You're Client1.";
  char server_message2[BUFSIZE] = "Welcome to the server! You're Client2. Wait for Client1's message!";
  char client_response[BUFSIZE];
  char client_response2[BUFSIZE];
  int message;

  //specify the server adress
  struct sockaddr_in server_adress;
  struct sockaddr_in client;
  struct sockaddr_in client2;
  server_adress.sin_family = AF_INET;
  server_adress.sin_port = htons(PORT_NO);
  server_adress.sin_addr.s_addr = INADDR_ANY;

  //create a server socket
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

  client_socket = accept(server_socket, NULL, NULL);
  if (server_socket < 0) {
     fprintf(stderr, "Can't accept socket\n");
     exit(4);
  }
  client_socket2 = accept(server_socket, NULL, NULL);
  if (server_socket < 0) {
     fprintf(stderr, "Can't accept socket\n");
     exit(4);
  }

  //send the greating message
  send(client_socket, server_message, sizeof(server_message), 0);
  printf("Message sent to client1\n"); //UI
  send(client_socket2, server_message2, sizeof(server_message2), 0);
  printf("Message sent to client2\n"); //UI

  //Chatting starts here
  while(1){

    //Recive greating message from Client1
    recv(client_socket, &client_response, sizeof(client_response), 0);

    //print out the client response
    printf("Client1 sent the following message:\n%s\n", client_response);

    //Send a message to Client2
    message = send(client_socket2, client_response, BUFSIZE, 0);
    if(message < 0) {
       fprintf(stderr, "Can't send message\n");
       exit(5);
    }

    //Recive greating message from Client2
    recv(client_socket2, &client_response2, sizeof(client_response2), 0);

    //print out the client response
    printf("Client2 sent the following message:\n%s\n", client_response2);

    //Send a message to Client1
    message = send(client_socket, client_response2, BUFSIZE, 0);
    if(message < 0) {
       fprintf(stderr, "Can't send message\n");
       exit(5);
    }

  }

  //close socket
  close(server_socket);
  close(client_socket);

  return 0;
}
