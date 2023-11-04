#pragma once

#include <stdint.h>
#include <ipv6.h>
#include <attribute.h>

typedef struct
{
    address_t src_addr;
    address_t dst_addr;
    uint32_t udp_len;
    uint32_t zeros : 12;
    uint8_t  next_hdr;
} attribute(packed) udp_ip;

typedef struct
{
    uint16_t port_src;
    uint16_t port_dest;
    uint16_t dg_len;
    uint16_t csum;
} attribute(packed) udp_hdr;

udp_hdr* udp_init(
    udp_hdr* hdr_ptr,
    uint16_t port_src,
    uint16_t port_dest,
    uint16_t dg_len,
    uint16_t csum
);