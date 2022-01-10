#include "pipe_networking.h"

int server_setup() {
    printf("creating socket\n");
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    getaddrinfo(NULL, "9001", hints, &results);  //Server sets node to NULL

    printf("binding socket\n");
    //create socket
    int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    bind(sd, results->ai_addr, results->ai_addrlen);

    printf("listening on socket\n");
    listen(sd, 10);

    printf("freeing stuff\n");
    free(hints);
    freeaddrinfo(results);

    return sd;
}

int server_connect(int sd) {
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);

    client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

    return client_socket;
}

int client_connect() {
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    getaddrinfo("127.0.0.1", "9001", hints, &results);  //Server sets node to NULL

    //create socket
    int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    connect(sd, results->ai_addr, results->ai_addrlen);;

    //DO STUFF

    free(hints);
    freeaddrinfo(results);

    return sd;
}