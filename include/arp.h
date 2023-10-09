#pragma once

#include <stdint.h>
#include <attribute.h>

typedef struct
{
    uint16_t htype;
    uint16_t ptype;
    uint8_t  hlen;
    uint8_t  plen;
    uint16_t oper;
    uint32_t sha;
    uint32_t spa;
    uint32_t tha;
    uint32_t tpa;
} attribute(packed) arp_header;