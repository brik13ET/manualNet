#pragma once

#include <stdint.h>
#include <attribute.h>
#include <arpa/inet.h>

#define mac(A,B,C,D,E,F) (mac_addr){A,B,C,D,E,F}

typedef uint8_t mac_addr[6];

typedef enum
{
    ARP = 0x0806,
    IPv4 = 0x0800,
    IPv6 = 0x86dd
}  attribute(packed) eth_t;

typedef struct 
{
    mac_addr src;
    mac_addr dest;
    eth_t type;

} attribute(packed) eth_hdr;

eth_hdr* eth_init(eth_hdr* hdr_ptr, mac_addr src, mac_addr dest);
