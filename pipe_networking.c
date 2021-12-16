#include "pipe_networking.h"

// self reminder- diagnostic print messages
// testing out something
/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {

    printf("Creating wkp...\n");
    int err = mkfifo(WKP, 0644);
    if(err == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Opening pipe to receive private FIFO name...\n");
    int to_server = open(WKP, O_RDONLY);
    if(to_server == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Reading private FIFO name...\n");
    char clientMessage[HANDSHAKE_BUFFER_SIZE];
    err = read(to_server, clientMessage, HANDSHAKE_BUFFER_SIZE);
    if(err == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Removing wkp...\n");
    remove(WKP);

    printf("Connecting to client FIFO...\n");
    *to_client = open(clientMessage, O_WRONLY);
    if(*to_client == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Sending ack...\n");
    err = write(*to_client, ACK, sizeof(ACK));
    if(err == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Receiving reponse from client...\n");
    err = read(to_server, clientMessage, sizeof(clientMessage));
    if(err == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    if(strcmp(clientMessage, ACK) != 0) {
        printf("3-Way Handshake Failed :(\n");
        return 0;
    }

    printf("3-Way Handshake Succeeded :)\n");

    return to_server;
}


/*=========================
client_handshake
args: int * to_server
Performs the client side pipe 3 way handshake.
Sets *to_server to the file descriptor for the upstream pipe.
returns the file descriptor for the downstream pipe.
=========================*/
int client_handshake(int *to_server) {
    printf("Creating private FIFO...\n");
    char pid[1000];
    sprintf(pid, "%d", getpid() );
    mkfifo(pid, 0644);

    printf("Opening wkp...\n");
    *to_server = open(WKP, O_WRONLY);
    if (*to_server == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Sending private FIFO name...\n");
    int err = write(*to_server, pid, HANDSHAKE_BUFFER_SIZE);
    if (err == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Receiving server ack message...\n");
    int from_server = open(pid, O_RDONLY);
    if (err == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    printf("Reading server ack message...\n");
    char clientMessage[HANDSHAKE_BUFFER_SIZE];
    err = read(from_server, clientMessage, HANDSHAKE_BUFFER_SIZE);

    printf("Removing secret pipe...\n");
    remove(pid);

    printf("Sending response to server...\n");
    err = write(*to_server, ACK, sizeof(ACK));
    if (err == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    return from_server;
}
