#include "pipe_networking.h"


char *toUpper(char line[]) {
    char * input = line;
    int i;
    // process input str into all caps
    for (i = 0; i < strlen(line); i++) {
        line[i] = toupper(line[i]);
    }
    return line;
}

int main() {
    int sd = server_setup();
    while(1) {
        int from_client = server_connect(sd);
        int f = fork();
        if(f) {
            close(from_client);
        } else {
            char message[BUFFER_SIZE];
            while(1) {
                char message[BUFFER_SIZE];
                int r = read(from_client, message, sizeof(message));
                if(r==0) break;
                toUpper(message);
                write(from_client, message, sizeof(message));
            }
        }
    }
}