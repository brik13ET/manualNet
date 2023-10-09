#pragma once

#include <stdint.h>
#include <attributes.h>

typedef struct
{
    uint16_t port_sender;
    uint16_t port_dest;
    uint16_t dg_len;
    uint16_t csum;
} attribute(packed) udp_hdr;