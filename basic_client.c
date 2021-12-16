#include "pipe_networking.h"


int main() {

    int to_server;
    int from_server;

    // Starts the handshake
    from_server = client_handshake( &to_server );

    char line[BUFFER_SIZE];
    while (1) {
        // Prompts user for input
        printf("Relay Message to Server: ");
        fgets(line, BUFFER_SIZE, stdin);
        
        write(to_server, line, sizeof(line)); // send data to server
        read(from_server, line, sizeof(line)); // reads processed data from server
        printf("Response From Server: %s\n", line); // displays processed data to server
    }
}
