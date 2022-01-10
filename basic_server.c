#include "pipe_networking.h"



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
                int i;
                for (i=0; i<strlen(message);i++){
                    message[i] = toupper(message[i]);
                }
                write(from_client, message, sizeof(message));
            }
        }
    }
}