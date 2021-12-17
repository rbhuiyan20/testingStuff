#include "pipe_networking.h"


int main() {

    int to_client;
    int from_client;

    while (1) {
        
        from_client = server_setup();
        
        //below is the subserver stuff
        int f = fork();
        
        // main server
        if (f) { 
        } else { 
            // forking server or sub server - completes handshake, communicates with server

            to_client = server_connect(from_client);
            char userIn[BUFFER_SIZE];
            while (1) { 
                //Reads in user input
                if (read(from_client, userIn, sizeof(userIn))==0) { 
                    break;
                }

                // makes user input all uppercase
                for(int i=0; i<strlen(userIn); i++) {
                    userIn[i] = toupper(userIn[i]);
                }
                //send data back to the user
                write(to_client, userIn, sizeof(userIn)); 
            }
        }
    }
}