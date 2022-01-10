#include "pipe_networking.h"


int main() {

    
    int sd = server_setup();

    while (1) {
        
        int from_client = server_connect(sd);

        //below is the subserver stuff
        int f = fork();
        if (f) { 

        } else { 
            // array of user input
            char userIn[BUFFER_SIZE];

            while (1) { 

                //Reads in user input
                if (read(from_client, userIn, sizeof(userIn))==0) { 
                    close(from_client);
                    break;
                }

                
                // makes user input all uppercase
                for(int i=0; i<strlen(userIn); i++) {
                    userIn[i] = toupper(userIn[i]);
                }

                //send data back to the user
                write(from_client, userIn, sizeof(userIn)); 
            }
        }
    }
}