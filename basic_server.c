#include "pipe_networking.h"


int main() {

   
    int sd = server_setup();

    while (1) {
        
        int from_client = server_connect(sd);


        // subserver stuff below
        int f = fork();
        if (f) { 

        } else { 
            char line[BUFFER_SIZE];

            while (1) { 
                // read in user input
                if (read(from_client, line, sizeof(line))==0) { 
                    int err = close(from_client);
                    }
                    break;
                }

                // makes user input all uppercase
                for(int i=0; i<strlen(userIn); i++) {
                    userIn[i] = toupper(userIn[i]);
                }
                // send data back to user
                write(from_client, line, sizeof(line)); 
            }
        }
    }
}