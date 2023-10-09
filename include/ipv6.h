#pragma once
#include <attributes.h>

typedef struct
{
    uint32_t octet[4];
} attribute(packed) address_t;

typedef struct
{
    uint8_t version : 4;
    uint8_t t_class;
    uint32_t flow_label : 20;

    uint16_t payload_len;
    uint8_t  next_hdr;
    uint8_t  hop_lim;

    address_t src_addr;
    address_t dest_addr;
} attribute(packed) ip_header;

ip_header ip_init(void);

address_t address_init(int o1, int o2, int o3, int o4);

