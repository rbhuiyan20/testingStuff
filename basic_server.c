#include "pipe_networking.h"


int main() {

    // listening for connection
    int sd = server_setup();

    while (1) {
        // accept client connection
        int from_client = server_connect(sd);

        int f = fork();
        if (f) { // server

        } else { // subserver
            char line[BUFFER_SIZE];

            while (1) { // Prompt client for input
                if (read(from_client, line, sizeof(line))==0) { // reads data from client
                    close(from_client);
                    break;
                }

                // process string to all lower
                for(int i=0; i<strlen(line); i++) {
                    line[i] = tolower(line[i]);
                }

                write(from_client, line, sizeof(line)); // send data to client
            }
        }
    }
}