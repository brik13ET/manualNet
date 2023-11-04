#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <net/if.h>  
#include <sys/socket.h>


extern struct sockaddr_ll addr;
extern socklen_t ad_len;
extern int sd;
extern int result;


int8_t init
(
    char* interfaceName
);
void deinit
(

);

int sendTo
(
    uint8_t* buf,
    size_t arr_len
);

uint8_t* recvFrom
(
    uint8_t* buf,
    size_t buf_siz,
    int offset
);