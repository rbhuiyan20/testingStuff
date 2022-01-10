#include "pipe_networking.h"


int main() {
    int sd = client_connect();
    char userIn[BUFFER_SIZE];
    while(1) {
        // while client runs, prompt user for input
        printf("input: ");
        fgets(userIn, sizeof(userIn), stdin);

        // send input to server
        write(sd, userIn, sizeof(userIn));

        // get the processed output from the server
        read(sd, userIn, sizeof(userIn));
        
        // print it for the user
        printf("Output: %s", userIn);
    }
}