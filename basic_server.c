#include "pipe_networking.h"


int main() {

    int to_client;
    int from_client;

    while (1) {
        from_client = server_setup();

        int f = fork();
        if (f) { // server

        } else { // subserver
            char line[BUFFER_SIZE];
            to_client = server_connect(from_client);

            while (1) { // Prompt client for input
                if (read(from_client, line, sizeof(line))==0) { // reads data from client
                    break;
                }

                // process string to all lower
                for(int i=0; i<strlen(line); i++) {
                    line[i] = tolower(line[i]);
                }

                write(to_client, line, sizeof(line)); // send data to client
            }
        }
    }
}
