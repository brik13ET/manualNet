#pragma once
#include <attributes.h>

typedef struct
{
    uint8_t version : 4;
    uint8_t t_class;
    uint32_t flow_label : 20;

    uint16_t payload_len;
    uint8_t  next_hdr;
    uint8_t  hop_lim;

    uint32_t src_addr[4];
    uint32_t dest_addr[4];
} attribute(packed) ip_header;

ip_header ip_init(void);