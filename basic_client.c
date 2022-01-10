#include "pipe_networking.h"


int main() {
    int sd = client_connect();
    char line[BUFFER_SIZE];
    while(1) {
        // while client runs, prompt user for input
        printf("input: ");
        fgets(line, sizeof(line), stdin);
        // send input to server
        write(sd, line, sizeof(line));
        // get the processed output from the server
        read(sd, line, sizeof(line));
        // print it for the user
        printf("Output: %s", line);
    }
}