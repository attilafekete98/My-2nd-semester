/*
This is a program to manage a debate between two clients. The clients can send messages to each
other. When both clients send the message "yes", the debate is closed.
This server program sends messages between two clients. When both clients sent a message
to the server, the server forwards it to the other client.

Usage: ./server

Made my Attila Fekete in 2018.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1301
#define PORT_NO 2001

int main(int argc, char *argv[] ){

  printf("\e[1;1H\e[2J"); //clears the screen on linux

  int server_socket;
  int client_socket;
  int client_socket2;
  char buffer[BUFSIZE];
  char server_message[BUFSIZE] = "Welcome to the server! You're Client1.";
  char server_message2[BUFSIZE] = "Welcome to the server! You're Client2.";
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

  //send the greating message
  send(client_socket, server_message, sizeof(server_message), 0);
  printf("Greating sent to client1\n"); //UI

  client_socket2 = accept(server_socket, NULL, NULL);
  if (server_socket < 0) {
     fprintf(stderr, "Can't accept socket\n");
     exit(4);
  }

  //send the greating message
  send(client_socket2, server_message2, sizeof(server_message2), 0);
  printf("Greating sent to Client2\n"); //UI

  //Chatting starts here
  while(1){

    //Chek if both messages is "yes", if so then close the debate
    if((strstr(client_response, "yes") != NULL) && (strstr(client_response2, "yes") != NULL)){
      /*strstr() Checks where it's second argument can be found in it's first argument.
        when it can't be found it returns NULL. So when both responses return NULL, it means
        that both clients are happy with the debate*/
      printf("Debate closed\n");
      //Send a message to Client2
      message = send(client_socket2, "Debate closed\n", BUFSIZE, 0);
      if(message < 0) {
         fprintf(stderr, "Can't send message\n");
         exit(5);
      }
      //Send a message to Client1
      message = send(client_socket, "Debate closed\n", BUFSIZE, 0);
      if(message < 0) {
         fprintf(stderr, "Can't send message\n");
         exit(5);
      }
      break;
    }

    //Recive greating message from Client1
    recv(client_socket, &client_response, sizeof(client_response), 0);

    //print out the client response
    printf("Client1 sent the following message:\n%s\n", client_response);

    //Send a message to Client2
    message = send(client_socket2, strcat(client_response, "222"), BUFSIZE, 0);
    //strcat() concatenates the two char arrays. This is the "translation"
    if(message < 0) {
       fprintf(stderr, "Can't send message\n");
       exit(5);
    }

    //Recive greating message from Client2
    recv(client_socket2, &client_response2, sizeof(client_response2), 0);

    //print out the client response
    printf("Client2 sent the following message:\n%s\n", client_response2);


    //Send a message to Client1
    message = send(client_socket, strcat(client_response2, "111"), BUFSIZE, 0);
    //strcat() concatenates the two char arrays. This is the "translation"
    if(message < 0) {
       fprintf(stderr, "Can't send message\n");
       exit(5);
    }

  }

  //close sockets
  close(server_socket);
  close(client_socket);
  close(client_socket2);

  return 0;
}
